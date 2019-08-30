#include<stdio.h>

void func1(int N)
{
	int i,j;
	for(i=1;i<=N;i++)
	{
		for(j=0;j<i;j++)
			printf("*");
		printf("\n");
	}
}
void func2(int 	N)
{
	int i,j;
	func1(N);
	for(i=N-1;i>0;i--)
	{
		for(j=0;j<i;j++)
			printf("*");
		printf("\n");
	}
}
void func3(int N)
{
	int i,j,k;
	k=1;
	for(i=N-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
			printf(" ");
		for(j=0;j<k;j++)
			printf("*");
		printf("\n");
		k+=2;
	}
}
int main()
{
	int N;
	int flag=0;
	printf("Please, Enter a number: ");
	while(!flag)
	{
		scanf("%d",&N);
		if(N>0)
			flag=1;
	}
	printf("Func1: \n");
	func1(N);
	printf("Func2: \n");
	func2(N);
	printf("Func3: \n");
	func3(N);


	return 0;
}

