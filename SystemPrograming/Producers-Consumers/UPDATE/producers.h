#ifndef PRODUCERS_H
#define PRODUCERS_H

typedef struct producersStruct producersStruct;

void createProducers(producersStruct** ps,size_t size);
void insertProducers(Q2* q2,producersStruct* ps);
void joinProducers(producersStruct* ps);
void* producer(void* buffer);
void* delete2(void* bp);

#endif