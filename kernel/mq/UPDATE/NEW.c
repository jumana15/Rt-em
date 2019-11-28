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

//#define DO_COPY

//#define DO_MUTEX

//#define DO_WAITQUEUE

//#define DO_WAKEUP

static int mq_count = 8;

static dev_t first_dev;
/*module_param(pipes_count, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(pipes_count, "How many pipes to create ?");
static int pipe_size = PAGE_SIZE*10;
module_param(pipe_size, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(pipe_size, "What is the pipe size ?");
static dev_t first_dev;*/

struct m_Q 
{
	struct list_head myList;
	size_t size;
	//size_t read_pos;
	//size_t write_pos;
	wait_queue_head_t read_queue;
	wait_queue_head_t write_queue;
	#ifdef DO_SPINLOCK
		spinlock_t lock;
	#endif /* DO_SPINLOCK */
	struct device *mq_device;
	#ifdef DO_MUTEX
		struct inode *inode;
		struct mutex mutex;
	#endif /* DO_MUTEX */
	int readers;
	int writers;
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
	//pipe->data = kmalloc(pipe_size, GFP_KERNEL);
	q->size = 0;
	/*pipe->read_pos = 0;
	pipe->write_pos = 0;*/
	#ifdef DO_SPINLOCK
		spin_lock_init(&q->lock);
	#endif /* DO_SPINLOCK */
	#ifdef DO_MUTEX
		mutex_init(&(q->mutex));
	#endif
	q->mq_device = NULL;
	init_waitqueue_head(&q->read_queue);
	init_waitqueue_head(&q->write_queue);
	q->readers = 0;
	q->writers = 0;
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

	/*int qNumber = iminor(inode)-MINOR(first_dev);//0-8
	struct m_Q* q = mQueues+qNumber;
	filp->private_data = q;*/
	filp->private_data=mQueues+iminor(inode)-MINOR(first_dev);
	/*mq_lock(q);
	if (filp->f_mode & FMODE_READ)
		q->readers++;
	if (filp->f_mode & FMODE_WRITE)
		q->writers++;
	mq_unlock(q);*/
	return 0;
}

static int mq_release(struct inode *inode, struct file *filp)
{
	/*struct m_Q* q;
	q=(struct m_Q*)(filp->private_data);
	mq_lock(q);
	if (filp->f_mode & FMODE_READ)
		q->readers--;
	if (filp->f_mode & FMODE_WRITE)
		q->writers--;
	wake up readers since they may want to end if there
	are no more writers...
	if (filp->f_mode & FMODE_WRITE) {
		if (q->writers == 0) {
			pr_debug("pipe_release: no more writers, waking up readers...\n");
			pipe_wake_readers(pipe);
		}
	}
	mq_unlock(q);*/
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

static inline int waitRead(struct m_Q* mq)
{
	int ret;
	/*#ifdef DO_WAITQUEUE*/
		mq_lock(mq);
		ret=wait_event_interruptible(mq->write_queue,!isEmpty(mq));
		if(!ret)
		{
			mq_unlock(mq);
		}
		return ret;
	/*#endif  DO_WAITQUEUE*/ 
	/*#ifdef DO_WAITQUEUE_RISQUE
	int ret;
	pipe_unlock(pipe);
	ret = wait_event_interruptible(pipe->read_queue,
			pipe_data(pipe) > 0 || pipe->writers == 0);
	pipe_lock(pipe);
	return ret;
	#endif 
	#ifdef DO_SCHEDULE
	int ret;
	DEFINE_WAIT(wait);
	prepare_to_wait(&pipe->read_queue, &wait, TASK_INTERRUPTIBLE);
	pipe_unlock(pipe);
	schedule();
	if (signal_pending(current))
		ret = -ERESTARTSYS;
	else
		ret = 0;
	finish_wait(&pipe->read_queue, &wait);
	pipe_lock(pipe);
	return ret;
	#endif */
	#ifdef DO_NOTHING
	return 0;
	#endif  /*DO_NOTHING */
}

static inline int waitWrite(struct m_Q* mq)
{
	int ret;
	/*#ifdef DO_WAITQUEUE*/
	mq_lock(mq);
	ret=wait_event_interruptible(mq->write_queue,!isFull(mq));
	if(!ret)
	{
		mq_unlock(mq);
	}
	return ret;
	/*#endif  DO_WAITQUEUE*/ /* DO_WAITQUEUE */
	/*#ifdef DO_WAITQUEUE_RISQUE
	int ret;
	pipe_unlock(pipe);
	ret = wait_event_interruptible(pipe->write_queue, pipe_room(pipe) > 0);
	pipe_lock(pipe);
	return ret;
	#endif 
	#ifdef DO_SCHEDULE
	int ret;
	DEFINE_WAIT(wait);
	prepare_to_wait(&pipe->write_queue, &wait, TASK_INTERRUPTIBLE);
	pipe_unlock(pipe);
	schedule();
	if (signal_pending(current))
		ret = -ERESTARTSYS;
	else
		ret = 0;
	finish_wait(&pipe->write_queue, &wait);
	pipe_lock(pipe);
	return ret;
	#endif *//* DO_SHCEDULE */
	#ifdef DO_NOTHING
	return 0;
	#endif /* DO_NOTHING */
}

static long mq_ioctl(struct file *file, unsigned int cmd,unsigned long arg)
{
	struct message_struct r;
	struct message_struct* argp = (struct message_struct*) arg;
	struct m_Q* mq=file->private_data;
	struct kernel_list_element *my_new_kernel_list_element;
	//struct list_head *next;
	struct kernel_list_element *elem;
	long ret;
	char* my_buf;
	switch (cmd) 
	{
		case MQ_SEND_MESSAGE:
			/*while(isFull(mq)&&(!waitWrite(mq)))
			{
				if(waitWrite(mq))
				{
					mq_lock(mq);
				}
			}*/
			/*while(!waitWrite(mq))
			{

			}*/
		if(!isFull(mq))
		{
			mq_lock(mq);
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
			/*print_queue(mq);*/
			mq_unlock(mq);
			/*wake_up_all(&mq->read_queue);*/
			return r.size;
		}
		return 100;
			break;
		case MQ_RECV_MESSAGE:
			/*while((isEmpty(mq))&&(!waitRead(mq)))
			{
				if(waitRead(mq))
				{
					mq_lock(mq);
				}
			}*/
			/*while(!waitRead(mq))
			{

			}*/
		if(!isEmpty(mq))
		{
			mq_lock(mq);
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
			/*wake_up_all(&mq->write_queue);*/
			return elem->size;
		}
		return 100;
			break;
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
	/*.read = mq_read,
	.write = mq_write,*/
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

