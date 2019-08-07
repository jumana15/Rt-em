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
void swap(int* a,int*b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;

}
int occur_most(int* a,int size)
{
	int i,j,max_V,max=0,counter=0;
	for(i=0;i<size;i++)
	{
		counter=1;
        if((max!=0)&&(max_V==a[i]))
            continue;
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
int even_odd(int* a,int size)
{
	int i,j,flag,tmp,counter=0;
	for(i=0;i<size-1;i++)
	{
        if(a[i]%2==0)
        {
            counter++;
        }
	}
	for(i=0;i<size-1;i++)
	{
		flag=1;
		for(j=0;j<size-1-i;j++)
		{
			if((a[j]%2==1)&&(a[j+1]%2==0))
			{
				swap(&a[j],&a[j+1]);
				flag=0;
			}
		}
		if(flag)
			return counter;/*break;*/
	}
	return counter;
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
int Binary_search(int* a,int size,int x)
{
	int i,j,med,low=0,high=size-1;
	while(low<=high)
	{
		med=(high-low)/2 + low;
		if(a[med]==x)
		{
			return med;
		}
		if(a[med]>x)
		{
			high=med-1;
		}
		if(a[med]<x)
		{
			low=med+1;
		}
	}
	return -1;
}
int main()
{

	int x,i,arr[N];
	scan_array(arr,N);
	/* 0/1 sort*/
	/*arr[N]={0,1,0,1,0,1,0,1,0,1};//{1,1,1,1,1,1,1,1,0,0}
	order(arr,N);*/
	print_array(arr,N);
	/*occur the most*/
	x=occur_most(arr,N);
	printf("\n%d occur the most\n",x);
	/*Even/Odd sort*/
	even_odd(arr,N);
	printf("\nEven/Odd sort:\n");
	print_array(arr,N);
	/*Bubble Sort*/
	/*printf("Sorted array: \n");
	Bubble_Sort(arr,N);
	print_array(arr,N);*/

	return 0;
}
