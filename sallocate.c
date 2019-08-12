#include<stdio.h>
#include<stdlib.h>
#include "sallocate.h"
DA_t* createDA(int size)
{
    DA_t* s=(DA_t*)malloc(sizeof(DA_t));
    s->size=size;
    s->index=0;
    s->arr=(intPtr*)malloc(size*sizeof(intPtr));
    return s;
}
int insert(DA_t* s,intPtr num)
{
    intPtr* ip;
	if((s->index)<(s->size))
	{
		s->arr[s->index]=num;
		return 1;
	}
	ip=(intPtr*)realloc(s->arr,(s->size*2)*sizeof(intPtr));
	if(!ip)
		return 0;
    	s->arr=ip;
	s->arr[(s->size)]=num;
	((s->size))*=2;
	return 1;
}
void printDA(DA_t* s)
{
    int i;
    for(i=0;i<(s->index);i++)
		printf("%d\t",*s->arr[i]);
}
void destroyDA(DA_t* s)
{
	int i;
    	if(s) {
		for(i=0;i<(s->index);i++) {
			free(s->arr[i]);
		}        	
		free(s->arr);
    		free(s);
	}
}
