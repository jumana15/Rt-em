#ifndef ALLOCATE_H
#define ALLOCATE_H

void* memInit(void* buffer,unsigned int *size);
void* memAlloc(void* buffer,unsigned int size,unsigned int newSize);
void memFree(void* buffer,void* freePointer,unsigned int size);
int printArray(void* buffer,unsigned int size);

#endif