#include<stdio.h>
#include<stdlib.h>
#include "h.h"

struct darray
{
	void** arr;
	size_t size;
	size_t index;
};

void swap(int* a,int*b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;

}

AdtStatus darrayCreate(darray** dArr,size_t initial_capacity)
{
    *dArr=(darray*)malloc(sizeof(darray));
	if(initial_capacity<=0)
		initial_capacity=1;
	(*dArr)->arr=(void**)malloc(initial_capacity*sizeof(void*));
	if(!(*dArr)->arr)
		return AllocationError;
	(*dArr)->size=initial_capacity;
	(*dArr)->index=0;
	return OK;
}

AdtStatus darrayDestroy(darray *dArr, elementDestroy destroyFunc, void *context)
{
	int i;
	if(dArr)
	{
		if(dArr->arr)
			for(i=0;i<dArr->index;i++)
				destroyFunc(dArr->arr[i],&context);
		free(dArr);
		return OK;
	}
	return AllocationError;
}

AdtStatus  darrayAdd(darray *dArr, void *_item)
{
	void **ip;
	if(!dArr)
		return  AllocationError;
	if(dArr->index==dArr->size)
	{
		ip=(void**)realloc(dArr->arr,(dArr->size*2)*sizeof(void*));
        if(!ip)
            return AllocationError;
        dArr->size*=2;
        dArr->arr=ip;
	}
	dArr->arr[dArr->index]=_item;
	dArr->index++;
	return OK;
}

AdtStatus   darrayDelete(darray *dArr,  void** _item)
{
    if((!dArr)||(dArr->index==0))
		return  AllocationError;
	dArr->index--;
	*_item=dArr->arr[dArr->index];
		if((dArr->size>=2)&&(2*dArr->index<dArr->size))
    	{
       		 dArr->arr=(void**)realloc(dArr->arr,(dArr->size/2)*sizeof(void*));
       		 dArr->size/=2;
    	}
	return OK;

}

AdtStatus   darrayGet(darray *dArr, size_t _index, void **_item)
{
	if((!dArr)||(_index<0)||(_index>=dArr->index))
		return  AllocationError;
	*_item=dArr->arr[_index];
	return OK;
}

AdtStatus   darraySet(darray *dArr, size_t _index, void  *_item)
{
	if((!dArr)||(_index<0)||(_index>=dArr->index))
		return  AllocationError;
	/*destroyFunc(dArr->arr[_index],&context)*/
	dArr->arr[_index]=_item;
	return OK;
}

AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if(!dArr)
		return  AllocationError;
	*_numOfItems=dArr->index;
    /*printf("index=%d\n",dArr->index);*/

	return OK;
}

AdtStatus darraySort(darray *dArr, elementCompare cmpFunc, size_t arraySize)
{
    int cmp,i,j,flag;
	if((!dArr)||(arraySize<0)||(arraySize>dArr->index))
		return  AllocationError;
	for(i=0;i<arraySize-1;i++)
	{
		flag=1;
		for(j=0;j<arraySize-1-i;j++)
		{
			cmp=cmpFunc(dArr->arr[j],dArr->arr[j+1]);
			if(cmp>0)
			{
				swap(dArr->arr[j],dArr->arr[j+1]);
				flag=0;
			}

		}
		if(flag)
			return OK;
	}
    return OK;

}