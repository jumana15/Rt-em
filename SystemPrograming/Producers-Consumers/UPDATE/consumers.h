#ifndef CONSUMERS_H
#define CONSUMERS_H

typedef struct consumersStruct consumersStruct;

void createConsumers(consumersStruct** cn,size_t size);
void deleteConsumers(Q2* q2,consumersStruct* cn);
void joinConsumers(consumersStruct* cn);
void* consumer(void* buffer);

#endif