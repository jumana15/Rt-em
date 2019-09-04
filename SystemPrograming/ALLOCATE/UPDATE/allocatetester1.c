#include<stdio.h>
#include<stdlib.h>
#include"allocate.h"
/*void testMemAlloc(void* buffer,unsigned int size)
{
	unsigned int i;
	int* bf=(int*)buffer;
	int* p;
	do
	{

	}
	while(p)
}*/
int main()
{
	unsigned int size=68;
	void* pr=malloc(size);
	void *a0,*a1,*a2,*a5,*a7,*a10,*a11,*a12,*a13;
	if(pr)
	{	
		pr=memInit(pr,&size);
		printf("size=%u\n",size);
		printArray(pr,size);
		printf("*\n*\n");
		
		a0=memAlloc(pr,size,1*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");

		a1=memAlloc(pr,size,1*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");

		a2=memAlloc(pr,size,3*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");

		a5=memAlloc(pr,size,2*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");

		a7=memAlloc(pr,size,2*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");
		
		memFree(pr,a1,size);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,a0,size);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,a5,size);
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,a7,size);
		printArray(pr,size);
		printf("*\n*\n");
		
		a10=memAlloc(pr,size,4*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");
		
		a11=memAlloc(pr,size,2*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");

		a12=memAlloc(pr,size,3*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");

		memFree(pr,&((int*)pr)[12],size);
		printArray(pr,size);
		printf("*\n*\n");

		a13=memAlloc(pr,size,6*sizeof(int));
		printArray(pr,size);
		printf("*\n*\n");
		printf("a13=%s",a13==NULL?NULL:"NOT");
	}
	free(pr);
	return 0;
}