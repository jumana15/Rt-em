#ifndef MQ_H
#define MQ_H

#define MQ_SEND_MESSAGE 16
#define MQ_RECV_MESSAGE 17
#define MQ_PRINT_SIZES 18

#pragma pack(push, 1)
struct message_struct
{
	char* buf;
	int size;
};
#pragma pack(pop)

/*struct m_Q 
{
	struct list_head myList;
	size_t size;
	//size_t read_pos;
	//size_t write_pos;
	wait_queue_head_t read_queue;
	wait_queue_head_t write_queue;
	struct device *mq_device;
	#ifdef DO_MUTEX
		struct inode *inode;
		struct mutex mutex;
	#endif
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

static inline void mq_ctor(struct m_Q* q);

static void mq_dtor(struct m_Q* q);

static inline bool isEmpty(struct m_Q* q);

static inline bool isFull(struct m_Q* q);

static inline void mq_lock(struct m_Q* q);

static inline void mq_unlock(struct m_Q* q);*/

/*static int mq_open(struct inode *inode, struct file *filp);*/

/*static int mq_release(struct inode *inode, struct file *filp);

static long mq_ioctl(struct file *file, unsigned int cmd,unsigned long arg);

static struct class *my_class;

static struct cdev cdev;

static int first_minor;

static int __init mq_init(void);

static void __exit mq_exit(void);*/

#endif
