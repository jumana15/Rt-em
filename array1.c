#include<stdio.h>
#define N 10
void order(int* array,int size)
{
	int i,counter=0;
	for(i=0;i<size;i++)
		if(array[i]==0)
			counter++;
	for(i=0;i<size;i++)
	{
		if(counter>0)
		{
			array[i]=0;
			counter--;
		}
		else
			array[i]=1;	
	}
}
void print_array(int* array,int size)
{
	int i;
	for(i=0;i<size;i++)
		printf("%d ",array[i]);
	printf("\n");
}
void scan_array(int* array,int size)
{
	int i;
	printf("Please enter %d numbers: ",size);
	for(i=0;i<size;i++)
		scanf("%d",&array[i]);
}
int occur_most(int* a,int size)
{
	int i,j,max_V,max=0,counter=0;
	for(i=0;i<size;i++)
	{
		counter=1;
		for(j=i;j<size;j++)
		{
			if(a[i]==a[j])
				counter++;

		}
		if(counter>max)
		{
			max=counter;
			max_V=a[i];
		}
	}
	return max_V;
}
/*void even_odd_with_an_extra_array(int* a,int size)
{
	int arr[N];
	int i,counter_even=0,counter_odd=size-1;
	for(i=0;i<size;i++)
	{
		if(a[i]%2==0)
		{
			arr[counter_even]=a[i];
			counter_even++;
		}
		if(a[size-i-1]%2==1)
		{
			arr[counter_odd]=a[size-i-1];
			counter_odd--;
		}
	}
	for(i=0;i<size;i++)
		a[i]=arr[i];
}*/
void even_odd(int* a,int size)
{	
	int i,j,flag,tmp;
	for(i=0;i<size-1;i++)
	{
		flag=1;
		for(j=0;j<size-1-i;j++)
		{
			if((a[j]%2==1)&&(a[j+1]%2==0))
			{
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				flag=0;
			}
		}
		if(flag)
			return;
	}
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
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				flag=0;
			}

		}
		if(flag)
			return;
	}
}
int main()
{
	
	int x,i,arr[N];/*={1,1,1,1,1,1,1,1,0,0};/*={0,1,0,1,0,1,0,1,0,1};*/
	scan_array(arr,N);
	/*order(arr,N);*/
	print_array(arr,N);
	x=occur_most(arr,N);
	printf("\n %d occur the most\n",x);
	even_odd(arr,N);
	/*Bubble_Sort(arr,N);*/
	print_array(arr,N);

	return 0;
}
