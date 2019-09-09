#ifndef WQUEUE_H
#define WQUEUE_H

#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

typedef struct {
    void** queue;
    size_t size;
    size_t count;
    size_t top;
	size_t last;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
} buffer_t;

buffer_t *buffer;

int create();
int isFull();
int isEmpty();
int pop(void** str);
int push(void* str);
void destroy();

#endif