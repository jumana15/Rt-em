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
		return 0;
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
	return 0;
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
	pthread_mutex_lock(&buffer->mutex);
    while(buffer->count <= 0)
        pthread_cond_wait(&buffer->more, &buffer->mutex);
	if(isEmpty(buffer))
	{
		/*mutex->waitable*/
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
    buffer->count++;
    
  	printf("Producer:%s\n",(char*)item);

    pthread_cond_signal(&buffer->more);
    pthread_mutex_unlock(&buffer->mutex);
    return 1;
}

void destroyQueue(buffer_t* buffer)
{
	if(!(buffer->queue))
		return;
	while(!isEmpty(buffer))
	{
		free((buffer->queue)[(buffer->top)++]);
		(buffer->top)%=(buffer->size);
		(buffer->count)--;
	}
	free(buffer->queue);
	free(buffer);
}

/*int main()
{
	char* s;
	size_t size=10;
	create(size);
	push("jumana");
	push("rayan");
	pop((void**)(&s));
	/*pop((void**)(&s));*/
	/*printf("counter=%lu.\n",buffer->count);
	printf("string=%s\n",s);
	return 0;
}*/
