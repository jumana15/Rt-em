#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"
#include "producers.h"
#include "consumers.h"
void createQ2(Q2** q2,size_t size)
{
	(*q2)=(Q2*)malloc(sizeof(Q2));
	if(!(*q2))
		exit(1);
	createQueue(&((*q2)->buffer),size);
    	createQueue(&((*q2)->bp),size);

}
void destroyQ2(Q2* q2)
{
	if(!q2)
		return;
	destroyQueue(q2->buffer);
    	destroyQueue(q2->bp);		
	free(q2);
}
int main()
{
	Q2* q2;
	producersStruct* ps;
	consumersStruct* cn;
    	size_t size=10;
	count=97;
    	count2=48;
    	createQ2(&q2,size);
    	createProducers(&ps,3);
    	createConsumers(&cn,3);
    	insertProducers(q2,ps);
    	deleteConsumers(q2,cn);
    	joinProducers(ps);
    	joinConsumers(cn);
	destroyQ2(q2);
  	return 0;
}
