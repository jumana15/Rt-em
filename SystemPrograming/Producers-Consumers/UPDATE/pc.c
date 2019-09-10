#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"

void* producer(void* item)
{
    pthread_mutex_lock(&buffer->mutex);
    while (buffer->count >= buffer->size)
        pthread_cond_wait(&buffer->less,&buffer->mutex);
    push(item);
    printf("String=%s\n",item);
    pthread_cond_signal(&buffer->more);
    pthread_mutex_unlock(&buffer->mutex);
    return;
}

void* consumer(void* item)
{
    pthread_mutex_lock(&buffer->mutex);
    while(buffer->count <= 0)
        pthread_cond_wait(&buffer->more, &buffer->mutex);
    pop(&item);
    pthread_cond_signal(&buffer->less);
    pthread_mutex_unlock(&buffer->mutex);
}

/*int main()
{
  char* s;
  size_t size=10;
  create(size);
  producer("jumana");
  producer("rayan");
  consumer((void**)(&s));
  /*pop((void**)(&s));*/
  /*printf("counter=%lu.\n",buffer->count);
  printf("string=%s\n",s);
  return 0;
}*/
int main()
{
    int status;
    size_t i,j;
    char* item;
    void* s;
    size_t size=10;
    
    create(size);
    for(i=0;i<15;i++)
    { 
      item=(char*)malloc(15*sizeof(char));
      if(!item)
        exit(1);
      for(j=0;j<14;j++)
        item[j]=(char)97+i;
      item[14]='\0';
      printf("Producer:i=%lu\t%s\n",i,item);
      status=pthread_create(&(thr[i]),NULL,producer,item);
      if(status)
        exit(1);
    }
    /*for(i=0;i<15;i++)
    {
      pthread_join(thr[i],NULL);
    }*/
    for(i=15;i<30;i++)
    { 
      status=pthread_create(&(thr[i]),NULL,consumer,item);
      if(status)
        exit(1);
      /*printf("Consumer:count=%lu\tString=%s.\n",buffer->count,item);
    */}
    printf("Done!\n");

  return 0;
}