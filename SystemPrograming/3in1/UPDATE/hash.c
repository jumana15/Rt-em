#include<stdio.h>
#include<stdlib.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include"hash.h"

struct Node
{
	void* key;
	void* value;
	struct Node* next;
};

hashArr* createHash(size_t size,size_t mutexSize,hashFunc hf,cmpFunc cmpf,printFunc pf)
{
	int i;
	hashArr* h=(hashArr*)malloc(sizeof(hashArr));
	if(!h)
		return NULL;
	h->buckets=(hashNode*)calloc(1.5*size,sizeof(hashNode));
	h->size=1.5*size;
	h->hf=hf;
	h->cmpf=cmpf;
	h->pf=pf;
	h->mutexSize=mutexSize;
	h->counter=0;
	h->mutex=(pthread_mutex_t*)malloc((h->mutexSize)*sizeof(pthread_mutex_t));
	if(!h->mutex)
	{
		free(h);
		exit(1);
	}
	for(i=0;i<h->mutexSize;i++)
		pthread_mutex_init(&(h->mutex[i]), NULL);
	return h;
}

void destroyList(hashNode h)
{
	hashNode tmp=h->next;
	while(tmp)
	{
		free(h->key);
		free(h->value);
		free(h);
		h=tmp;
		tmp=tmp->next;
	}
	free(h);
}
void destroyHash(hashArr* h)
{
	int i;
	if(h)
	{
		if(h->buckets)
		{
			for(i=0;i<h->size;i++)
			{
				if(h->buckets[i])
				{
					destroyList(h->buckets[i]);
				}
			}
			free(h->buckets);
		}
		for(i=0;i<h->mutexSize;i++)
		{
			pthread_mutex_destroy(&h->mutex[i]);
		}
		free(h);
	}
}

static hashNode newNode(hashNode* node,void* key,void* val)
{
	*node=(hashNode)malloc(sizeof(struct Node));
	if(!node)
		return NULL;
	(*node)->next=NULL;
	(*node)->value=val;
	(*node)->key=key;
	return *node;
}

int insertHash(hashArr* h,void* key,void* val)
{
	hashNode node,prev,cur;
	size_t index=h->hf(key);
	int x;
	index%=(h->size);
	pthread_mutex_lock(&h->mutex[index%(h->mutexSize)]);
	x=findHash(h,&prev,&cur,key);
	if(x)
	{
		pthread_mutex_unlock(&h->mutex[index%(h->mutexSize)]);
		return 2;
	}
	if(newNode(&node,key,val))
	{
		node->next=h->buckets[index];
		h->buckets[index]=node;
		h->counter++;
		pthread_mutex_unlock(&h->mutex[index%(h->mutexSize)]);
		return 1;
	}
	pthread_mutex_unlock(&h->mutex[index%(h->mutexSize)]);
	return 0;
}

int deleteHash(hashArr* h,void* key)
{
	hashNode prev=NULL,cur=NULL;
	int x;
	size_t index=h->hf(key)%(h->size);
	pthread_mutex_lock(&h->mutex[index%(h->mutexSize)]);
	x=findHash(h,&prev,&cur,key);
	if(x)
	{
		if(prev)
		{
			prev->next=cur->next;
		}
		else
		{
			h->buckets[index]=cur->next;	
		}
		free(cur->key);
		free(cur->value);
		free(cur);
		h->counter--;
		pthread_mutex_unlock(&h->mutex[index%(h->mutexSize)]);
		return 1;
	}
	pthread_mutex_unlock(&h->mutex[index%(h->mutexSize)]);
	return 0;
}
int findHash(hashArr* h,hashNode* prev,hashNode* cur,void* key)
{
	size_t index=(h->hf(key))%(h->size);
	for((*cur)=h->buckets[index];(*cur)!=NULL;(*cur)=(*cur)->next)
	{

		if(h->cmpf((*cur)->key,key)==0)
		{	
			return 1;
		}
		(*prev)=(*cur);
	}
	return 0;
}

void forEachHash(hashArr* h)
{
	size_t counter=0;
	size_t i;
	hashNode node;
	if(h)
	{
		if(h->buckets)
		{
			for(i=0;i<h->size;i++)
			{
				if(h->buckets[i])
				{
					node=h->buckets[i];
					do
					{
						counter++;
						printf("i=%lu,",i);
						/*printf("index=%lu:",(h->hf(h->buckets[i]->key))%(h->size));*/
						h->pf(node->key,node->value);
						node=node->next;
					}
					while(node);
				}
			}
		}
	}
	printf("\nHash contain %lu items.\n",counter);
}