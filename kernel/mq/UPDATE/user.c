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
#include <assert.h>

void* readM(void* data)
{
	int myid=*(int*)data;
	struct message_struct m;
	int i,fd,ret;
	char filename[256];
	#define SIZE_OF_BUFFER 10
	char str[SIZE_OF_BUFFER];
	srand(time(0));
	for(i=0;i<80;i++)
	{
		/*j=rand()%8;*/
		sprintf(filename, "/dev/mq%d", i%8);
		/*printf("readM\n%s\n",filename);*/
		fd=open(filename,O_RDWR);
		if(fd==-1) 
		{
			fprintf(stderr, "open error [%s]\n", filename); 
			exit(1);
		}
        m.buf=str;
		m.size=SIZE_OF_BUFFER;
		printf("reader %d going into IOCTL\n", myid);
		ret=ioctl(fd,MQ_RECV_MESSAGE,&m);
		if(ret==-1)
		{
			fprintf(stderr, "ioctl error\n"); 
			exit(1);
		}
		printf("reader %d out of IOCTL\n", myid);
		/*printf("the message is %s\n", m.buf);*/
		ret=close(fd);
		if(ret==-1) 
		{
			fprintf(stderr, "close error\n"); 
			exit(1);
		}
	}
	printf("reader ended\n");
	/*free(m.buf);*/
	return NULL;
}

void* writeM(void* data)
{
	int myid=*(int*)data;
	struct message_struct m;
	int i,j,fd,ret;
	char str[3];
	/*char s[8]="/dev/mq_";*/
	char filename[256];
	str[0]=53;
	srand(time(0));
	for(i=0;i<8;i++)
	{
		/*j=rand()%8;
		s[strlen(s)-1]=j+48;*/
		sprintf(filename, "/dev/mq%d", (i+7)%8);
		/*printf("writeM\n%s\n",filename);*/
		fd=open(filename,O_RDWR); 
		if(fd==-1) 
		{
			fprintf(stderr, "open error\n"); 
			exit(1);
		}
	    /*char* str=(char*)malloc(4096);
		printf("Enter MSG:\n");
		scanf("%s",str);*/
		str[1]=i+48;
		str[2]='\0';
		m.buf=str;
		m.size=strlen(str);
		for(j=0;j<10;j++)
		{
			printf("writer %d going into IOCTL\n", myid);
			ret=ioctl(fd,MQ_SEND_MESSAGE,&m);
			if(ret==-1) 
			{
				fprintf(stderr, "ioctl error\n"); 
				exit(1);
			}
			printf("writer %d out of IOCTL\n", myid);
			assert(ret==m.size);
		}
		ret=close(fd);
		if(ret==-1) 
		{
			fprintf(stderr, "close error\n"); 
			exit(1);
		}
	}
	printf("writer ended\n");
	/*free(m.buf);*/
	return NULL;
}

int main()
{
	const int number_of_writers=10;
	const int number_of_readers=10.;
	pthread_t* thr_writers=(pthread_t*)malloc(sizeof(pthread_t)*number_of_writers);
	pthread_t* thr_readers=(pthread_t*)malloc(sizeof(pthread_t)*number_of_readers);
	for (int i = 0; i < number_of_writers; i++) 
    {
    	int* data=(int*)malloc(sizeof(int));
    	*data=i;
    	int status=pthread_create(thr_writers+i,NULL,writeM, data);
		if(status) {
			fprintf(stderr, "problem with pthread_create\n");
	    	exit(1);
		}
	}
	for (int i=0; i< number_of_readers; i++) {
		int* data=(int*)malloc(sizeof(int));
    	*data=i;
	    int status=pthread_create(thr_readers+i,NULL,readM, data);
		if(status) {
			fprintf(stderr, "problem with pthread_create\n");
	    	exit(1);
		}
    }
    for(int i=0;i<number_of_readers;i++)
	{
		pthread_join(thr_readers[i],NULL);
	}
	for(int i=0;i<number_of_writers;i++)
	{
		pthread_join(thr_writers[i],NULL);
	}
	return 0;
}
