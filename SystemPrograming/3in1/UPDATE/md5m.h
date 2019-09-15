#ifndef MD5M_H
#define MD5M_H

#include <sys/param.h>
#include <pthread.h> 
#include <semaphore.h> 

pthread_mutex_t mutexMD5;
sem_t semMD5;
int md5Func(unsigned char* c,char* filename);

#endif