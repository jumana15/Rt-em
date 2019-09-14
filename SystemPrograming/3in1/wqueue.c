#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include "wqueue.h"

struct buffer_t{
    void** queue;
    size_t size;
    size_t count;
    size_t top;
	size_t last;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
};

int createQueue(buffer_t** buffer,size_t size)
{
	char** x;
	*buffer=(buffer_t*)malloc(sizeof(buffer_t));
	if(!buffer)
	{
		exit(1);
	}
	x=(char**)malloc(size*sizeof(char*));
	if(x)
	{
		(*buffer)->queue=(void**)x;
		(*buffer)->size=size;
		(*buffer)->top=-1;
		(*buffer)->last=-1;
		(*buffer)->count=0;
		pthread_mutex_init(&((*buffer)->mutex),NULL);
		pthread_cond_init(&((*buffer)->more), NULL);
		pthread_cond_init(&((*buffer)->less), NULL);
		return 1;
	}
	free(*buffer);
	exit(1);
}

int isFull(buffer_t* buffer)
{
	return buffer->count == buffer->size;
}

int isEmpty(buffer_t* buffer)
{
	return buffer->count == 0;
}

int pop(buffer_t* buffer,void** item)
{
	int flag;
	pthread_mutex_lock(&buffer->mutex);
    while(buffer->count <= 0)
        pthread_cond_wait(&buffer->more, &buffer->mutex);
    flag=isEmpty(buffer);
	if(flag)
	{
		printf("Queue Underflow \n");
        return 0;
    }
	assert(buffer->count > 0);
	*item=buffer->queue[buffer->top++];
	buffer->top %=buffer->size;
	buffer->count--;
	pthread_cond_signal(&buffer->less);
    pthread_mutex_unlock(&buffer->mutex);
	return 1;
}

int push(buffer_t* buffer,void* item)
{
	pthread_mutex_lock(&buffer->mutex);
    while (buffer->count >= buffer->size)
        pthread_cond_wait(&buffer->less,&buffer->mutex);
    if(isFull(buffer))
    {
    	/*mutex->waitable*/
        printf("Something Going Wrong!\n");
        return 0;
    }
	if((buffer->top)==-1)
		buffer->top=0;
	buffer->last=((buffer->last)+1)%(buffer->size);
	assert(buffer->count < buffer->size);
    buffer->queue[buffer->last]=item;
    /*printf("POP:%s->Size:%lu\n",((((char**)buffer->queue)[buffer->last])),buffer->count);
    */buffer->count++;
    pthread_cond_signal(&buffer->more);
    pthread_mutex_unlock(&buffer->mutex);
    return 1;
}

void destroyQueue(buffer_t* buffer)
{
	if(!buffer)
		return;
	if(!(buffer->queue))
	{
		free(buffer);
		return;
	}
	while(!isEmpty(buffer))
	{
		
		free((buffer->queue)[(buffer->top)++]);
		(buffer->top)%=(buffer->size);
		(buffer->count)--;
	}
	pthread_mutex_destroy(&buffer->mutex);
	pthread_cond_destroy(&buffer->less);
	pthread_cond_destroy(&buffer->more);
	free(buffer->queue);
	free(buffer);
}
void printq (buffer_t* buffer)
{
	size_t i;
	for(i=buffer->top;i<buffer->count+buffer->top;i++)
		printf("i=%lu\t %s\n",i,(char*)(buffer->queue[i]));

}