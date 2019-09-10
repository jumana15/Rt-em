#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"
#include "producers.h"

struct producersStruct{
    pthread_t* thr;
    size_t size;
};

void createProducers(producersStruct** ps,size_t size)
{
	*ps=(producersStruct*)malloc(sizeof(producersStruct));
	if(!(*ps))
		exit(1);
	(*ps)->thr=(pthread_t*)malloc(size*sizeof(pthread_t));
	if(!((*ps)->thr))
	{
		free(*ps);
		exit(1);
	}
	(*ps)->size=size;
}

void insertProducers(Q2* q2,producersStruct* ps)
{
	size_t i,k;
	int status;
	for(k=0;k<3;k++)
	{
		
	    
	      status=pthread_create(&(ps->thr[k]),NULL,producer,(void*)q2);
	      if(status)
	        exit(1);
	    
	}
}

void joinProducers(producersStruct* ps)
{
	int i;
	for(i=0;i<3;i++)
    {
      pthread_join(ps->thr[i],NULL);
  	}
}
void* producer(void* q2)
{

	size_t i,j;
	char* item;	
	for(i=0;i<10;i++)
	{
		item=(char*)malloc(15*sizeof(char));
		if(!item)
		    exit(1);
		for(j=0;j<14;j++)
		{
		    item[j]=count;
		}	  
		count++;    
		item[14]='\0';
		push(((Q2*)q2)->buffer,item); 
		pop(((Q2*)q2)->bp,(void**)(&item));
		printf("Deleted Item=%s\n",item);
	}
}