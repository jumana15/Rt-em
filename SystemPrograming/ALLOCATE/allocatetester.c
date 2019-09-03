#include<stdio.h>
#include<stdlib.h>
#include"allocate.h"

int main()
{
	unsigned int size=17;
	void* pr=calloc(size,4);
	if(pr)
	{	
		pr=memInit(pr,&size);
		printf("size=%u\n",size);
		printArray(pr,size);
		printf("*\n*\n");
		
		memAlloc(pr,size,1);
		printArray(pr,size);
		printf("*\n*\n");

		memAlloc(pr,size,1);
		printArray(pr,size);
		printf("*\n*\n");

		memAlloc(pr,size,3);
		printArray(pr,size);
		printf("*\n*\n");

		memAlloc(pr,size,2);
		printArray(pr,size);
		printf("*\n*\n");

		memAlloc(pr,size,2);
		printArray(pr,size);
		printf("*\n*\n");
		
		memFree(pr,&((int*)pr)[1],size);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,&((int*)pr)[0],size);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,&((int*)pr)[5],size);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,&((int*)pr)[7],size);
		printArray(pr,size);
		printf("*\n*\n");
		
		memAlloc(pr,size,4);
		printArray(pr,size);
		printf("*\n*\n");
		
		memAlloc(pr,size,2);
		printArray(pr,size);
		printf("*\n*\n");

		memAlloc(pr,size,3);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,&((int*)pr)[12],size);
		printArray(pr,size);
		printf("*\n*\n");

		memAlloc(pr,size,6);
		printArray(pr,size);
		printf("*\n*\n");
	}
	free(pr);
	return 0;
}