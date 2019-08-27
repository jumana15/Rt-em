#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"
size_t hashFunction(void* str)
{
	size_t h=5381;
	int c;
	char s[15];
	strcpy(s,(char*) str);
	c=(*s)++;
	while(c)
	{
		h=((h<<5)+h)+c;/*hash*33+c*/
		c=(*s)++;
	}
	return h;
}
void printFunction(void* key,void* value)
{
	printf("Key=%s\tValue=%s\n",(char*)key,(char*)value);
}
int cmpFunction(void* a,void* b)
{
	return strcmp((char*)a,(char*)b);
}
int createTest(hashFunc hf,cmpFunc cmpf,printFunc pf)
{
	hashArr *h;
	size_t i=0,size=100000;
	for(i=0;i<size;i++)
	{
		h=createHash(i,hf,cmpf,pf);
		if(!h)
		{
			printf("Create Function Failed! i=%lu\n",i);
			return 0;
		}
		if(h)
		{
			destroyHash(h);
			h=NULL;
		}
	}
	printf("Create Function Succeeded i=%lu.\n",i);
	printf("Destroy Function Succeeded i=%lu.\n",i);
	return 1;
}
int insertTest(hashArr** h,hashFunc hf,cmpFunc cmpf,printFunc pf)
{
	size_t i=0,size=100000;
	char *s1,s2[]="done!";
	if(*h)
		destroyHash(*h);
	(*h)=createHash(size/2,hf,cmpf,pf);
	if(!(*h))
	{
		printf("Failed Allocate!");
		return 0;
	}
	for(i=0;i<2*size;i++)
	{
		s1=(char*)malloc(15*sizeof(char));
		sprintf(s1,"%lu",i);
		if(!insertHash(*h,s1,s2))
		{
			printf("Insert Function Failed! i=%lu\n",i);
			return 0;
		}
		if(i%3==0)
		{
			if(!insertHash(*h,s1,"set!"))
			{
				printf("Insert Function Failed! i=%lu\n",i);
				return 0;
			}

		}
	}
	forEachHash(*h);
	printf("Insert Function Succeeded i=%lu\n",i);
	return 1;
}
int deleteTest(hashArr** h)
{
	size_t i=0,size=100000;
	char s1[15];
	int x;
	if(!(*h))
	{
		printf("Insert Function Failed!\n");
	}
	for(i=0;i<3*size;i++)
	{
		if(i%2==1)
		{
			sprintf(s1,"%lu",i);
			x=deleteHash(*h,s1);
			if((!x)&&(i<2*size))
			{
				printf("Found Function Failed! i=%lu.\n",i);
				printf("Delete Function Failed! i=%lu.\n",i);
				return 0;
			}

		}
	}
	forEachHash(*h);
	printf("Delete Function Succeeded i=%lu.\n",i);
	printf("Find Function Succeeded i=%lu.\n",i);
	return 1;
}

int main()
{
	hashFunc hf=hashFunction;
	printFunc pf=printFunction;
	cmpFunc cmpf=cmpFunction;
    hashArr* h=NULL;
    createTest(hf,cmpf,pf);
    if(insertTest(&h,hf,cmpf,pf))
    	deleteTest(&h);
    return 0;
}