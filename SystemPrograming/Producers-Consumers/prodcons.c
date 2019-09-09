#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"
#include "producers.h"

int main()
{
    int status;
    size_t i,j;
    char* s;
    size_t size=10;
    pthread_t thr[30];
    create(size);
    for(i=0;i<15;i++)
    { 
      s=(char*)malloc(15*sizeof(char));
      for(j=0;j<14;j++)
        s[j]=(char)97+i;
      s[14]='\0';
      printf("i=%lu -> %s\n",i,s);
      status=pthread_create(&(thr[i]),NULL,producer,(void*)s);
      if(status)
        exit(1);
    }
    for(i=15;i<30;i++)
    { 
      status=pthread_create(&(thr[i]),NULL,consumer,(void**)(&s));
      if(status)
        exit(1);
      printf("count=%lu\tString=%s.\n",buffer->count,s);
    }
    printf("Done!\n");

  return 0;
}