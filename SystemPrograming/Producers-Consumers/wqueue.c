#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include "wqueue.h"

int create(size_t size)
{
	char** x;
	buffer=(buffer_t*)malloc(sizeof(buffer_t));
	if(!buffer)
	{
		return 0;
	}
	x=(char**)malloc(size*sizeof(char*));
	if(x)
	{
		buffer->queue=(void**)x;
		buffer->size=size;
		buffer->top=-1;
		buffer->last=-1;
		buffer->count=0;
		pthread_mutex_init(&(buffer->mutex),NULL);
		pthread_cond_init(&(buffer->more), NULL);
		pthread_cond_init(&(buffer->less), NULL);
		return 1;
	}
	free(buffer);
	return 0;
}

int isFull()
{
	return buffer->count == buffer->size;
}

int isEmpty()
{
	return buffer->count == 0;
}

int pop(void** item)
{
	if(isEmpty())
	{
		/*mutex->waitable*/
		printf("Queue Underflow \n");
        return 0;
    }
	assert(buffer->count > 0);
	*item=buffer->queue[buffer->top++];
	buffer->top %=buffer->size;
	buffer->count--;
	return 1;
}

int push(void* item)
{
    if(isFull())
    {
    	/*mutex->waitable*/
        printf("Queue Overflow \n");
        return 0;
    }
	if ((buffer->top)==-1)
		buffer->top=0;
	buffer->last=((buffer->last)+1)%(buffer->size);
	assert(buffer->count < buffer->size);
    buffer->queue[buffer->last]=item;
    buffer->count++;
    return 1;
}

void destroy()
{
	if(!(buffer->queue))
		return;
	while(!isEmpty())
	{
		free((buffer->queue)[(buffer->top)++]);
		(buffer->top)%=(buffer->size);
		(buffer->count)--;
	}
	free(buffer->queue);
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
