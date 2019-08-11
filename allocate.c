#include<stdio.h>
#include<stdlib.h>
int* insert(int num,int* arr,int* size,int* index)
{	int* ip;
	if(*index<*size)
	{
		arr[*index]=num;
		return arr;
	}
	ip=(int*)realloc(arr,((*size)*2)*sizeof(int));
	if(!ip)
	{
		exit(1);
	}
	ip[*size]=num;
	(*size)*=2;
	index=ip+(index-arr);	
	return ip;
}
int main()
{
	int i,size,num,index=0;
	int *arr,*check;
	while(1)
	{
		printf("Please enter the array size:\n");	
			scanf("%d",&size);
		if(size>0)
		{
			arr=(int*)malloc(size*sizeof(int));
			if(!arr)
				exit(1);
			break;
		}
	}
	while(1)
	{
		printf("\nPlease enter a number :\n");	
		scanf("%d",&num);
		if(num==-5)
			break;
		check=insert(num,arr,&size,&index);
		if(!check)
			break;
		arr=check;
		index++;
		printf("\nsize=%d\n",size);
	}
	arr=(int*)realloc(arr,index*sizeof(int));
	for(i=0;i<index;i++)
		printf("%d\t",arr[i]);
	printf("\nsize=%d\n",index);
	free(arr);
	return 0;
}
