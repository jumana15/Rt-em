#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"
#include "producers.h"

void producer(void* item)
{
    pthread_mutex_lock(&buffer->mutex);
    while (buffer->count >= buffer->size)
        pthread_cond_wait(&buffer->less,&buffer->mutex);
    push(item);
    pthread_cond_signal(&buffer->more);
    pthread_mutex_unlock(&buffer->mutex);
}