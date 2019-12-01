#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <linux/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>

typedef struct 
{
    char myRandomData[24];
    char nothing[40];
}queue_data;

GAsyncQueue* q;

void check_zero(int ret) 
{
    if(ret!=0) 
    {
        fprintf(stderr, "failed!\n");
        exit(1);
    }
}

void* randomTh()
{
	int i,result;
	//char* myRandomData;
	queue_data* rs;
	char* s="/dev/urandom";
	char end[21]="End!";
	int randomData = open(s,O_RDONLY);
	/*arc4random_buf(myRandomData, sizeof myRandomData); */
	if (randomData < 0)
	{
	    fprintf(stderr, "open error\n"); 
			exit(1);
	}
	for(i=0;i<100000;i++)
	{
		/*rs=(queue_data*)malloc(sizeof(queue_data));*/
		result=posix_memalign((void**)&rs, 64, sizeof(queue_data));
    	check_zero(result);
		rs->myRandomData[20]='\0';
	    result = read(randomData, rs->myRandomData, sizeof(strlen(rs->myRandomData)));
	    if (result < 0)
	    {
	        fprintf(stderr, "error\n"); 
			return NULL;
	    }
	    g_async_queue_push(q,rs);
	}
	result=posix_memalign((void**)&rs, 64, sizeof(queue_data));
    check_zero(result);
    strcpy(rs->myRandomData,end);
	g_async_queue_push(q,rs);
	result=posix_memalign((void**)&rs, 64, sizeof(queue_data));
    check_zero(result);
    strcpy(rs->myRandomData,end);
	g_async_queue_push(q,rs);
	return NULL;
}

void* readTh()
{
	int i;
	size_t sum;
	queue_data* msg;
	while(1)
	{
		sum=0;
		msg=g_async_queue_pop(q);
		if(!strcmp(msg->myRandomData,"End!"))
		{
			free(msg);
			break;;
		}
		for(i=0;i<strlen(msg->myRandomData);i++)
		{
			sum+=msg->myRandomData[i];
		}
		/*fprintf(stderr,"The Message Is: %s, Sum= %lu\n",msg->myRandomData,sum);*/
		free(msg);
	}
	return NULL;
}
int main()
{
	int i,status;
	pthread_t thr[3];
	q= g_async_queue_new();
   	status=pthread_create(&(thr[0]),NULL,randomTh,NULL);
	if(status)
    	exit(1);
    for(i=1;i<3;i++)
    {
	    status=pthread_create(&(thr[i]),NULL,readTh,NULL);
		if(status)
	    	exit(1);
    }
	for(i=0;i<3;i++)
	{
		pthread_join(thr[i],NULL);
	}
	return 0;
}