#include<stdio.h>
#include<stdlib.h>
#include "sallocate.h"
int main()
{
    int SarraySize,i,size,num,index=0;
    DA_t *Sarray,*ip;
    intPtr num_p;

	while(1)
	{
		printf("Please enter the number of arrays:\n");
        scanf("%d",&SarraySize);
		if(SarraySize>0)
		{
		    Sarray=(DA_t*)malloc(SarraySize*sizeof(DA_t));
            if(!Sarray)
            {
                printf("can't be allocated :(");
                return 0;
            }
            break;
		}
	}
	for(i=0;i<SarraySize;i++)
    {
        printf("\nArray %d:\n",i+1);
        while(1)
        {
            printf("Please enter the array size:\n");
            scanf("%d",&size);
            if(size>0)
            {
                ip=createDA(size);
		if(!ip)
                {
                    printf("Struct can't be allocated :(");
                    return 0;
		}
                Sarray[i]=*ip;
                if(!Sarray[i].arr)
                {
                    printf("Array can't be allocated :(");
                    return 0;
                }
                break;
            }
        }
        while(1)
        {
            printf("\nPlease enter a number :\n");
            scanf("%d",&num);
            if(num==-5)
                break;
  	    num_p=(intPtr)malloc(sizeof(int));
	    if(!num_p)
            {
            	printf("Size can't be allocated :(");
                return 0;
  	    }
	    *num_p=num;
            if(!insert(Sarray+i,num_p))
            {
                printf("there's no enough place :(");
                break;
            }
            Sarray[i].index++;
        }
        Sarray[i].arr=(intPtr*)realloc(Sarray[i].arr,(Sarray[i].index)*sizeof(intPtr));
        Sarray[i].size=Sarray[i].index;
        printf("Array final size = %d\n",Sarray[i].size);
        printDA(&Sarray[i]);
    }
    for(i=0;i<SarraySize;i++)
        destroyDA(&Sarray[i]);
	return 0;
}
