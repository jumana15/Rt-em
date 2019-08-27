#include<stdio.h>
#include<stdlib.h>
#include"hash.h"

struct Node
{
	void* key;
	void* value;
	struct Node* next;
};

hashArr* createHash(size_t size)
{
	size_t i=0;
	hashArr* h=(hashArr*)malloc(sizeof(hashArr));
	if(!h)
		return NULL;
	h->buckets=(hashNode*)calloc(1.5*size,sizeof(hashNode));
	if(!(h->buckets))
	{
		free(h);
		return NULL;
	}
	h->size=1.5*size;
	return h;
}

void destroyList(hashNode h)
{
	hashNode tmp=h->next;
	while(tmp)
	{
		free(h->value);
		free(h->key);
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

int insertHash(hashArr* h,void* key,void* val,hashFunc hf,cmpFunc cmpf)
{
	hashNode node,*prev,*cur;
	size_t index=hf(key);
	int x=findHash(h,prev,cur,key,hf,cmpf);
	index%=(h->size);
	if(x)
	{
		(*cur)->value=val;
		return 1;
	}
	if(newNode(&node,key,val))
	{
		node->next=h->buckets[index];
		h->buckets[index]=node;
		return 1;
	}
	return 0;
}
int deleteHash(hashArr* h,void* key,hashFunc hf,cmpFunc cmpf)
{
	hashNode node,*prev,*cur;
	int x=findHash(h,prev,cur,key,hf,cmpf);
	size_t index=hf(key)%(h->size);
	if(x)
	{
		if((prev)&&(*prev))
		{
			(*prev)->next=(*cur)->next;
		}
		else
		{
			h->buckets[index]=NULL;	
		}
		free((*cur)->key);
		free((*cur)->value);
		free(*cur);
		return 1;
	}
	return 0;
}
int findHash(hashArr* h,hashNode* prev,hashNode* cur,void* key,hashFunc hf,cmpFunc cmpf)
{
	size_t index=(hf(key))%(h->size);
	prev=NULL;
	for((*cur)=h->buckets[index];(*cur)!=NULL;(*cur)=(*cur)->next)
	{

		if(cmpf((*cur)->key,key)==0)
		{	
			return 1;
		}
		prev=cur;
	}
	return 0;
}

void forEachHash(hashArr* h,printFunc pf)
{
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
						pf(node->key,node->value);
						node=node->next;
					}
					while(node);
				}
			}
		}
	}
}


