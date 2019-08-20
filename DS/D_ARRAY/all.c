

#include<stdio.h>
#include<stdlib.h>

enum AdtStatus {OK, AllocationError};

typedef enum AdtStatus AdtStatus;

/* forward declaration of the darray type */

typedef struct darray darray;

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


int main()
{
    int x,num,flag=1;
    darray *arr;
    int* item;
    AdtStatus st;
    int size,index;
    while(1)
    {
        printf("Choose option:\n1->Create Array.\n2->Add.\n3->Delete.\n4->Set.\n5->Get.\n6->Items Number.\n7->Sort.\n8->Destroy.\n9->Print Array.\n10->Array Size.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
            printf("\nPlease, enter size:\n");
            scanf("%d",&size);
            if(size>=1)
            {
                st=darrayCreate(&arr,size);
                if(st)
                {
                        printf("AllocationError!\n");
                        return 0;
                }
            }
            else
                printf("Size cannot be less than one !\n");
            break;
            case 2:
                printf("\nPlease Enter a number:\n");
                scanf("%d",&num);
                st=darrayAdd(arr,num);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 3:
                st=darrayDelete(arr,item);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("The deleted item is: %d.\n",*item);
                }
                break;
            case 4:
                printf("\nPlease Enter an Index and an Item:\n");
                scanf("%d%d",&index,&num);
                st=darraySet(arr,index,num);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 5:
                 printf("\nPlease Enter an Index:\n");
                scanf("%d",&index);
                st=darrayGet(arr,index,item);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("Item=%d.\n",*item);
                }
                break;
            case 6:
                st=darrayItemsNum(arr,item);
                 if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("Number of Items =%d.\n",*item);
                }
                break;
            case 7:
                st=darraySort(arr,arr->index);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 8:
                st=darrayDestroy(arr);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 9:
                for(num=0;num<arr->index;num++)
                {
                    printf("%d\t",arr->arr[num]);
                }
                printf("\n");
                break;
            case 10:
                printf("%d\n",arr->size);
                break;
            default:
                flag=0;
                break;
        }
        if(!flag)
            break;
    }
    darrayDestroy(arr);
    return 0;
}
