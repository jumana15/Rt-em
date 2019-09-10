#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"
#include "consumers.h"

struct consumersStruct{
    pthread_t* thr;
    size_t size;
};

void createConsumers(consumersStruct** cn,size_t size)
{
	*cn=(consumersStruct*)malloc(sizeof(consumersStruct));
	if(!(*cn))
		exit(1);
	(*cn)->thr=(pthread_t*)malloc(size*sizeof(pthread_t));
	if(!((*cn)->thr))
	{
		free(*cn);
		exit(1);
	}
	(*cn)->size=size;
}

void deleteConsumers(Q2* q2,consumersStruct* cn)
{
	size_t i,k;
	char* item;
	int status;
	for(k=0;k<3;k++)
	{
	      status=pthread_create(&(cn->thr[k]),NULL,consumer,q2);
	      if(status)
	        exit(1);
	    
	}
}

void joinConsumers(consumersStruct* cn)
{
	int i;
	for(i=0;i<3;i++)
    {
      pthread_join(cn->thr[i],NULL);
  	}
}

void* consumer(void* q2)
{
	int i;
	char* item;
	for(i=0;i<10;i++)
	{
	    pop(((Q2*)q2)->buffer,(void**)(&item));
	    printf("Deleted Item=%s\n",item);
	    free(item);
	    item=(char*)malloc(2);
		item[0]=count2;
		item[1]='\0';  
		count2++; 
	    push(((Q2*)q2)->bp,(void*)item);
	}
}