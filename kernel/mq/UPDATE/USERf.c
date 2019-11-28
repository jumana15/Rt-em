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
#include <dirent.h>
#include <pthread.h> 
#include <semaphore.h> 
#include "mq.h"

void* readM()
{
	struct message_struct m;
	int i,fd,ret;
	char filename[256];
	#define SIZE_OF_BUFFER 10
	char str[SIZE_OF_BUFFER];
	srand(time(0));
	for(i=0;i<19616;i++)
	{
		/*j=rand()%8;*/
		sprintf(filename, "/dev/mq%d", i%8);
		/*printf("readM\n%s\n",filename);*/
		fd=open(filename,O_RDWR);
		if(fd==-1) 
		{
			fprintf(stderr, "%d open error [%s]\n",i, filename); 
			exit(1);
		}
        m.buf=str;
		m.size=SIZE_OF_BUFFER;
		ret=ioctl(fd,MQ_RECV_MESSAGE,&m);
		if(ret==-1)
		{
			fprintf(stderr, "ioctl error\n"); 
		}
		else
		{
			if(ret==100)
			{	
				printf("EMPTY!\n");
			}
			else
			{
				printf("the message is %s\n", m.buf);
			}
		}
		ret=close(fd);
		if(ret==-1) 
		{
			fprintf(stderr, "close error\n"); 
			exit(1);
		}
	}
	/*free(m.buf);*/
	return NULL;
}

void* writeM()
{
	struct message_struct m;
	int i,fd,ret;
	char str[3];
	/*char s[8]="/dev/mq_";*/
	char filename[256];
	str[0]=53;
	srand(time(0));
	for(i=0;i<19616;i++)
	{
		/*j=rand()%8;
		s[strlen(s)-1]=j+48;*/
		sprintf(filename, "/dev/mq%d", (i+1)%8);
		/*printf("writeM\n%s\n",filename);*/
		fd=open(filename,O_RDWR); 
		if(fd==-1) 
		{
			fprintf(stderr, "open error\n"); 
			exit(1);
		}
	    if (fd<0) 
	    { 
	        printf("\nError opend file\n"); 
	        exit(1);
	    }
	    /*char* str=(char*)malloc(4096);
		printf("Enter MSG:\n");
		scanf("%s",str);*/
		str[1]=i+48;
		str[2]='\0';
		m.buf=str;
		m.size=strlen(str);
		ret=ioctl(fd,MQ_SEND_MESSAGE,&m);
		if(ret==-1) 
		{
			fprintf(stderr, "ioctl error\n"); 
		}
		else
		{
			if(ret==100)
			{	
				printf("FULL!\n");
			}
			else
			{
				printf("the return value of ioctl is %d\n", ret);
			}
		}
		ret=close(fd);
		if(ret==-1) 
		{
			fprintf(stderr, "close error\n"); 
			exit(1);
		}
	}
	/*free(m.buf);*/
	return NULL;
}

int main()
{
	int i,status;
	pthread_t thr[200];
	for (i = 0; i < 100; i++) 
    {
    	status=pthread_create(&(thr[i]),NULL,writeM,NULL);
		if(status)
	    	exit(1);
	    status=pthread_create(&(thr[100+i]),NULL,readM,NULL);
		if(status)
	    	exit(1);
    }
   /* for(i=100;i<200;i++)
	{
		status=pthread_create(&(thr[i]),NULL,readM,NULL);
		if(status)
	    	exit(1);
	}*/
	for(i=0;i<200;i++)
	{
		pthread_join(thr[i],NULL);
	}
	return 0;
}
