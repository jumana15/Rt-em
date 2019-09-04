#include<stdio.h>
#include<stdlib.h>
#include"allocate.h"

#define IS_MSB(number) (number&(0x80000000))
#define SET_FREE(header) ((header)&(0x7fffffff))
#define SET_OCCUPIED(header) ((header)|(0x80000000))
#define SHIFT(number) ((number)<<31)
#define MOD4(number) ((number)&(~3))

void* memInit(void* buffer,unsigned int *size)
{
	int* bf=(int*)buffer;
	unsigned int i;
	(*size)/=4;
	bf=(int*)((((long)bf+3)/4)*4);
	*size=MOD4((*size)-(bf-(int*)buffer));
	bf[0]=*size;
	return bf;
}

void* memAlloc(void* buffer,unsigned int size,unsigned int newSize)
{
	int* bf=(int*)buffer;
	unsigned int s,sum=0,count=0,sum2=0;
	newSize=(newSize+3)/4;
	while(sum<size)
	{
		count=0;			
		sum2=SET_FREE(bf[count]);
		while((sum+sum2<=size)&&(!IS_MSB(bf[count])))
		{	
			if(sum2>=newSize)
			{
				s=sum2-newSize;
				bf[0]=SET_OCCUPIED(newSize);
				if(s)
					bf[newSize]=s;
				return (void*)bf;
			}
			if(sum+sum2==size)
			{
				break;
			}
			count+=bf[count];
			sum2+=SET_FREE(bf[count]);
		}
		bf+=sum2;
		sum+=sum2;
	}
	return NULL;
}

void memFree(void* buffer,void* freePointer,unsigned int size)
{
	int* bf=(int*)buffer;
	int* fp =(int*)freePointer;
	*fp=SET_FREE(fp[0]);
	if((fp+fp[0])<bf+size)
	{
		if(!IS_MSB(*(fp+fp[0])))
		{
			fp[0]+=*(fp+fp[0]);
		}
	}
}
int printArray(void* buffer,unsigned int size)
{
	int* bf=(int*)buffer;
	unsigned int i;
	for(i=0;i<size;i++)
	{
		if(bf[i])
		{
			printf("i=%u\tsize=%u\tallocated=%d\n",i,SET_FREE(bf[i]),IS_MSB(bf[i])!=0);
		}
	}

}
