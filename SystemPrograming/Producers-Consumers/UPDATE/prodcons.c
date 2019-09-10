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
int main()
{
	Q2* q2;
	producersStruct* ps;
	consumersStruct* cn;
    int status;
    size_t i,j;
    char* s;
    size_t size=10;
    createQ2(&q2,size);
    count=97;
    count2=48;
    createProducers(&ps,3);
    createConsumers(&cn,3);
    insertProducers(q2,ps);
    deleteConsumers(q2,cn);
    joinProducers(ps);
    joinConsumers(cn);
    /*destroy*/


  return 0;
}