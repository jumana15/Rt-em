#ifndef WQUEUE_H
#define WQUEUE_H

#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

int count;
int count2;

typedef struct buffer_t buffer_t;

typedef struct{
buffer_t* buffer;
buffer_t* bp;
}Q2;

int createQueue(buffer_t** buffer,size_t size);
int pop(buffer_t* buffer,void** item);
int push(buffer_t* buffer,void* item);
void destroyQueue(buffer_t* buffer);

#endif