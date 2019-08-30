
/* forward declaration of the darray type */

typedef struct darray darray;

​
struct darray
{
	int* arr;
	int size;
	int index;
}
/* Create a new dynamic array. Return its address in d_arr.

   The initial capacity is the number of items that can be stored

   before a new allocation is needed. */
void swap(int* a,int*b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;

}

void Bubble_Sort(int* a,int size)
{
	int i,j,flag,tmp;
	for(i=0;i<size-1;i++)
	{
		flag=1;
		for(j=0;j<size-1-i;j++)
		{
			if(a[j]>a[j+1])
			{
				swap(&a[j],&a[j+1]);
				flag=0;
			}

		}
		if(flag)
			return;
	}
}

AdtStatus darrayCreate(darray **dArr, size_t initial_capacity)
{
	if(initial_capacity<=0)
		initial_capacity=1;
	dArr->arr=(int*)malloc(initial_capacity*sizeof(int));
	if(!dArr->arr)
		return AllocationError;
	dArr->size=initial_capacity;
	dArr->index=0;
	return ok;
}

AdtStatus darrayDestroy(darray *dArr)
{
	if(dArr)
	{
		if(dArr->arr)
			free(dArr->arr);
		free(dArr);
		return ok;
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
	return ok;
}

AdtStatus   darrayDelete(darray *dArr,  int* _item)
{
	if((!dArr)||(index==0))
		return  AllocationError;
	dArr->index--;
	*_item=dArr[dArr->index];
	return ok;

}

AdtStatus   darrayGet(darray *dArr, size_t _index, int *_item)
{
	if((!dArr)||(_indrex<0)||(_index>=dArr->index))
		return  AllocationError;
	*_item=dArr[_index];
	if((dArr->size>=2)&&(2*dArr->index<dArr->size))
    {
        dArr->arr=(int*)realloc(dArr->arr,(dArr->size/2)*sizeof(int));
        dArr->size/=2;
    }
	return ok;
}

AdtStatus   darraySet(darray *dArr, size_t _index, int  _item)
{
	if((!dArr)||(_indrex<0)||(_index>=dArr->index))
		return  AllocationError;
	dArr[_index]=_item;
	return ok;
}

AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if(!dArr)
		return  AllocationError;
	*_numOfItems=dArr->index;
	return ok;
}

AdtStatus darraySort(darray *dArr, size_t arraySize)
{
	if((!dArr)||(arraySize<0)||(arraySize>=dArr->index))
		return  AllocationError;
	Bubble_Sort(dArr->arr,arraySize);
	return ok;

}
#endif

