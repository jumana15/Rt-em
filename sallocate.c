#include<stdio.h>
#include<stdlib.h>
#include "sallocate.h"
DA_t* createDA(int size)
{
    DA_t* s=(DA_t*)malloc(sizeof(DA_t));
    s->size=(int)size;
    s->index=0;
    s->arr=(int*)malloc(size*sizeof(int));
    return s;
}
int insert(DA_t* s,int num)
{
    int* ip;
	if((s->index)<(s->size))
	{
		s->arr[(int)s->index]=num;
		return 1;
	}
	ip=(int*)realloc(s->arr,(s->size*2)*sizeof(int));
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
		printf("%d\t",s->arr[i]);
}
void destroyDA(DA_t* s)
{
    if(s->arr)
        free(s->arr);
    free(s);
}
