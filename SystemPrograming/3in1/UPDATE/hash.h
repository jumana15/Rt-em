#ifndef HASH_H
#define HASH_H

#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

typedef struct Node* hashNode;

typedef size_t (*hashFunc)(void* s);
typedef int (*cmpFunc)(void* a,void* b);
typedef void (*printFunc)(void* a,void* b);

typedef struct{
	hashNode* buckets;
	size_t size;
	size_t mutexSize;
	size_t counter;
	pthread_mutex_t* mutex;
	hashFunc hf;
	cmpFunc cmpf;
	printFunc pf;
}hashArr;

hashArr* createHash(size_t size,size_t mutexSize,hashFunc hf,cmpFunc cmpf,printFunc pf);

void destroyHash(hashArr* h);

int insertHash(hashArr* h,void* key,void* val);

int deleteHash(hashArr* h,void* key);

int findHash(hashArr* h,hashNode* prev,hashNode* cur,void* key);

void forEachHash(hashArr* h);

#endif