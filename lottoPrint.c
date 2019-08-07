#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6
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
void Lotto_With_2D_Array()
{
	char array[5][10];
	int i,j,r,a,b;
	for(i=0;i<5;i++)
		for(j=0;j<10;j++)
			array[i][j]='-';
	array[4][9]=' ';
	srand(time(0));
	for(i=0;i<6;i++)
	{
		r=(rand()%49)+1;
		printf("%d\n",r);
		a=r%10-1;
		b=r/10;
		if(array[b][a]=='+')
			i--;
		else
			array[b][a]='+';
	}
	printf(" ");
	for(i=-1;i<5;i++)
	{	if(i==-1)
		{
			printf(" ");
			for(j=0;j<10;j++)
				printf(" %d",j+1);
			printf("\n ");
		}
		else
		{
			printf("%d",i);
			for(j=0;j<10;j++)
			{
				printf(" %c",array[i][j]);
			}
			printf("\n ");
		}
	}
	return;
}
void lotto()
{
   	int array[N];
	int i,j,r,a,b,flag,index=0;
	srand(time(0));
	while(index<N)
	{
	    flag=1;
		r=(rand()%49)+1;
		printf("%d\n",r);
		for(j=0;j<index;j++)
        {
            if(array[j]==r)
            {
                flag=0;
                continue;
            }
        }
        if(!flag)
            continue;
        array[index]=r;
        index++;
	}
	Bubble_Sort(array,N);
	index=0;
	for(i=-1;i<5;i++)
	{	if(i==-1)
		{
			printf("  ");
			for(j=0;j<10;j++)
				printf(" %d",j+1);
			printf("\n ");
		}
		else
		{
			printf("%d",i);
			for(j=1;j<=10;j++)
			{
			    if(array[index]==(10*i+j))
                {
                    printf(" %c",'+');
                    index++;
                }
                else
                {
                    if(!((i==4)&&(j==10)))
                    {
                        printf(" %c",'-');
                    }
                }
			}
			printf("\n ");
		}
	}
	return;
}
int main()
{
	lotto();
	return 0;
}
