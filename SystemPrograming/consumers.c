#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "wqueue.h"
#include "consumers.h"

void consumer(void** item)
{
    pthread_mutex_lock(&buffer->mutex);
    while(buffer->count <= 0)
        pthread_cond_wait(&buffer->more, &buffer->mutex);
    pop(item);
    pthread_cond_signal(&buffer->less);
    pthread_mutex_unlock(&buffer->mutex);
}