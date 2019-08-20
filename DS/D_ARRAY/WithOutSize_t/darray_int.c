#include<stdio.h>
#include<stdlib.h>
#include "darray_int.h"

struct darray
{
	int* arr;
	int size;
	int index;
};

void swap(int* a,int*b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;

}

AdtStatus darrayCreate(darray** dArr, int initial_capacity)
{
    *dArr=(darray*)malloc(sizeof(darray));
	if(initial_capacity<=0)
		initial_capacity=1;
	(*dArr)->arr=(int*)malloc(initial_capacity*sizeof(int));
	if(!(*dArr)->arr)
		return AllocationError;
	(*dArr)->size=initial_capacity;
	(*dArr)->index=0;
	return OK;
}

AdtStatus darrayDestroy(darray *dArr)
{
	if(dArr)
	{
		if(dArr->arr)
			free(dArr->arr);
		free(dArr);
		return OK;
	}
	return AllocationError;
}

AdtStatus   darrayAdd(darray *dArr,  int  _item)
{
	int *ip;
	if(!dArr)
		return  AllocationError;
	if(dArr->index==dArr->size)
	{
		ip=(int*)realloc(dArr->arr,(dArr->size*2)*sizeof(int));
        if(!ip)
            return AllocationError;
        dArr->size*=2;
        dArr->arr=ip;
	}
	dArr->arr[dArr->index]=_item;
	dArr->index++;
	return OK;
}

AdtStatus   darrayDelete(darray *dArr,  int* _item)
{
    if((!dArr)||(dArr->index==0))
		return  AllocationError;
	dArr->index--;
	*_item=dArr->arr[dArr->index];
		if((dArr->size>=2)&&(2*dArr->index<dArr->size))
    {
        dArr->arr=(int*)realloc(dArr->arr,(dArr->size/2)*sizeof(int));
        dArr->size/=2;
    }
	return OK;

}

AdtStatus   darrayGet(darray *dArr, int _index, int *_item)
{
	if((!dArr)||(_index<0)||(_index>=dArr->index))
		return  AllocationError;
	*_item=dArr->arr[_index];
	return OK;
}

AdtStatus   darraySet(darray *dArr, int _index, int  _item)
{
	if((!dArr)||(_index<0)||(_index>=dArr->index))
		return  AllocationError;
	dArr->arr[_index]=_item;
	return OK;
}

AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if(!dArr)
		return  AllocationError;
	*_numOfItems=dArr->index;
    printf("index=%d\n",dArr->index);

	return OK;
}

AdtStatus darraySort(darray *dArr, int arraySize)
{
    int i,j,flag;
	if((!dArr)||(arraySize<0)||(arraySize>dArr->index))
		return  AllocationError;
	for(i=0;i<arraySize-1;i++)
	{
		flag=1;
		for(j=0;j<arraySize-1-i;j++)
		{
			if(dArr->arr[j]>dArr->arr[j+1])
			{
				swap(&dArr->arr[j],&dArr->arr[j+1]);
				flag=0;
			}

		}
		if(flag)
			return OK;
	}
    return OK;

}