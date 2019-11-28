#include <linux/module.h> /* for MODULE_*, module_* */
#include <linux/moduleparam.h> /* for module_param, MODULE_PARM_DESC */
#include <linux/fs.h> /* for fops */
#include <linux/device.h> /* for class_create */
#include <linux/slab.h> /* for kmalloc, kfree */
#include <linux/cdev.h> /* for cdev_* */
#include <linux/sched.h> /* for TASK_INTERRUPTIBLE and more constants */
#include <linux/spinlock.h> /* for spinlock_t and ops on it */
#include <linux/wait.h> /* for wait_queue_head_t and ops on it */
#include <linux/uaccess.h> /* for copy_to_user, access_ok */
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/ioctl.h>
#include "mq.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("USER");
MODULE_DESCRIPTION("M_Q");

#define DO_MUTEX

static int mq_count = 8;

static dev_t first_dev;

struct m_Q 
{
	struct list_head myList;
	size_t size;
	wait_queue_head_t read_queue;
	wait_queue_head_t write_queue;
	struct device *mq_device;
	#ifdef DO_MUTEX
	struct mutex mutex;
	#endif /* DO_MUTEX */
};

static struct m_Q* mQueues;

struct kernel_list_element
{
	struct list_head next;
	char* buf;
	int size;
};

static inline void mq_ctor(struct m_Q* q)
{
	INIT_LIST_HEAD(&(q->myList));
	q->size = 0;
	#ifdef DO_MUTEX
	mutex_init(&(q->mutex));
	#endif
	q->mq_device = NULL;
	init_waitqueue_head(&q->read_queue);
	init_waitqueue_head(&q->write_queue);
}

static void mq_dtor(struct m_Q* q)
{
/* marks suspects this crashes the kernel*/
	while(!list_empty(&q->myList))
	{
		list_del((&q->myList)->next);
		q->size--;
	}
}

static inline bool isEmpty(struct m_Q* q)
{
	return q->size==0;
}

static inline bool isFull(struct m_Q* q)
{
	return q->size==10;
}

static inline void mq_lock(struct m_Q* q)
{
	#ifdef DO_MUTEX
	mutex_lock(&(q->mutex));
	#endif /* DO_MUTEX */
}

static inline void mq_unlock(struct m_Q* q)
{
	#ifdef DO_MUTEX
	mutex_unlock(&(q->mutex));
	#endif /* DO_MUTEX */
}

static int mq_open(struct inode *inode, struct file *filp)
{
	filp->private_data=mQueues+iminor(inode)-MINOR(first_dev);
	return 0;
}

static int mq_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/*void print_queue(struct m_Q* mq) 
{
  struct list_head * next;
  struct kernel_list_element * elem;*/
  /*printf("Queue:\n");*/
  /*list_for_each(next, &mq->myList) 
  {  
    elem = list_entry(next,struct kernel_list_element, next);*/
    /*printf("\t%d\n",elem->data);*/
  /*}
}*/

static inline int queue_has_elements(struct m_Q* mq)
{
	int ret;
	mq_lock(mq);
	ret=mq->size;
	if(!ret)
	{
		mq_unlock(mq);
	}
	return ret;
}

static inline int queue_has_space(struct m_Q* mq)
{
	int ret;
	mq_lock(mq);
	ret=!isFull(mq);
	if(!ret)
	{
		mq_unlock(mq);
	}
	return ret;
}

static long mq_ioctl(struct file *file, unsigned int cmd,unsigned long arg)
{
	struct message_struct r;
	struct message_struct* argp = (struct message_struct*) arg;
	struct m_Q* mq=file->private_data;
	struct kernel_list_element *my_new_kernel_list_element;
	struct kernel_list_element *elem;
	long ret;
	char* my_buf;
	switch (cmd) 
	{
		case MQ_SEND_MESSAGE:
			ret=wait_event_interruptible(mq->write_queue, queue_has_space(mq));
			if(ret==-ERESTARTSYS) {
				// no need to release mutex here
				return ret;
			}
			ret = copy_from_user(&r, argp, sizeof(r));
			if (ret) 
			{
				pr_err("%s: error in copy from user\n", THIS_MODULE->name);
				mq_unlock(mq);
				return ret;
			}
			my_buf=(char*)kmalloc(r.size, GFP_KERNEL);
			if(IS_ERR(my_buf)) 
			{
				pr_err("%s: error in kmalloc\n", THIS_MODULE->name);
				mq_unlock(mq);
				ret=PTR_ERR(my_buf);
				return ret;
			}
			ret=copy_from_user(my_buf, r.buf, r.size);
			if(ret) 
			{
				pr_err("%s: error in copy from user\n", THIS_MODULE->name);
				mq_unlock(mq);
				return ret;	
			}
			my_new_kernel_list_element=kmalloc(sizeof(struct kernel_list_element), GFP_KERNEL);
			my_new_kernel_list_element->buf=my_buf;
			my_new_kernel_list_element->size=r.size;
			list_add_tail(&my_new_kernel_list_element->next,&mq->myList);
			mq->size++;
			mq_unlock(mq);
			wake_up_all(&mq->read_queue);
			return r.size;
			break;
		case MQ_RECV_MESSAGE:
			ret=wait_event_interruptible(mq->read_queue, queue_has_elements(mq));
			if(ret==-ERESTARTSYS) {
				// no need to release mutex here
				return ret;
			}
			elem=list_entry((&mq->myList)->next,struct kernel_list_element,next);
			ret = copy_from_user(&r, argp, sizeof(r));
			if (ret) {
				pr_err("%s: error in copy from user\n", THIS_MODULE->name);
				mq_unlock(mq);
				return ret;
			}
			ret=copy_to_user(r.buf, elem->buf, elem->size);
			if (ret) {
				pr_err("%s: error in copy to user\n", THIS_MODULE->name);
				mq_unlock(mq);
				return ret;
			}
			list_del((&mq->myList)->next);
			kfree(elem->buf);
			kfree(elem);
			mq->size--;
			mq_unlock(mq);
			wake_up_all(&mq->write_queue);
			return elem->size;
		default:
			return -ENOTTY;
	}
	return -ENOTTY; 
}

static const struct file_operations mq_fops = 
{
	.owner = THIS_MODULE,
	.open = mq_open,
	.release = mq_release,
	.unlocked_ioctl = mq_ioctl,
};
/* this variable will store the class */
static struct class *my_class;
/* this variable will hold our cdev struct */
static struct cdev cdev;
/* this is our first minor (0 by default)*/
static int first_minor;

static int __init mq_init(void)
{
	int ret;
	int i;
	mQueues = kmalloc(sizeof(struct m_Q)*mq_count,GFP_KERNEL);
	if (IS_ERR(mQueues)) 
	{
		pr_err("kmalloc\n");
		ret = PTR_ERR(mQueues);
		goto err_return;
	}

	for (i = 0; i < mq_count; i++)
	{
		mq_ctor(mQueues+i);
	}
	/* allocate our own range of devices */
	ret = alloc_chrdev_region(&first_dev, first_minor, mq_count,THIS_MODULE->name);
	if (ret) 
	{
		pr_err("cannot alloc_chrdev_region\n");
		goto err_final;
	}
	//pr_debug("allocated the region\n");
	/* add the cdev structure */
	cdev_init(&cdev, &mq_fops);
	ret = cdev_add(&cdev, first_dev, mq_count);
	if (ret) 
	{
		pr_err("cannot cdev_add\n");
		goto err_dealloc;
	}
	pr_debug("added the cdev\n");
	/* this is creating a new class (/proc/devices) */
	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) 
	{
		pr_err("class_create\n");
		ret = PTR_ERR(my_class);
		goto err_cdev_del;
	}
	pr_debug("created the class\n");
	for (i = 0; i < mq_count; i++) 
	{
		/* and now lets auto-create a /dev/ node */
		mQueues[i].mq_device = device_create(my_class, NULL,MKDEV(MAJOR(first_dev), MINOR(first_dev)+i),NULL, "%s%d", THIS_MODULE->name, i);
		if (IS_ERR(mQueues[i].mq_device)) 
		{
			pr_err("device_create\n");
			ret = PTR_ERR(mQueues[i].mq_device);
			goto err_class;
		}
	}
	pr_info(KBUILD_MODNAME " loaded successfully\n");
	return 0;
	/*
err_device:
	for (i = 0; i < pipes_count; i++) {
		device_destroy(my_class, MKDEV(MAJOR(first_dev),
			MINOR(first_dev)+i));
	}
	*/
err_class:
	class_destroy(my_class);
err_cdev_del:
	cdev_del(&cdev);
err_dealloc:
	unregister_chrdev_region(first_dev, mq_count);
err_final:
	for (i = 0; i < mq_count; i++)
		mq_dtor(mQueues+i);
	kfree(mQueues);
err_return:
	return ret;
}

static void __exit mq_exit(void)
{
	int i;
	for (i = 0; i <mq_count; i++)
	{
		device_destroy(my_class, MKDEV(MAJOR(first_dev),MINOR(first_dev)+i));
	}
	class_destroy(my_class);
	cdev_del(&cdev);
	unregister_chrdev_region(first_dev, mq_count);
	for (i = 0; i < mq_count; i++)
	{
		mq_dtor(mQueues+i);
	}
	kfree(mQueues);
	pr_info(KBUILD_MODNAME " unloaded successfully\n");
}
module_init(mq_init);
module_exit(mq_exit);


