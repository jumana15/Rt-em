#ifndef HASH_H
#define HASH_H

typedef struct Node* hashNode;

typedef size_t (*hashFunc)(void* s);
typedef int (*cmpFunc)(void* a,void* b);
typedef void (*printFunc)(void* a,void* b);

typedef struct{
	hashNode* arr;
	size_t size;
}hashArr;

hashArr* createHash(size_t size);

void destroyHash(hashArr* h);

int insertHash(hashArr* h,void* key,void* val,hashFunc hf,cmpFunc cmpf);

int deleteHash(hashArr* h,void* key,hashFunc hf,cmpFunc cmpf);

int findHash(hashArr* h,hashNode prev,hashNode n,void* key,hashFunc hf,cmpFunc cmpf);

void forEachHash(hashArr* h,printFunc pf);

#endif