#include<stdio.h>
#include<stdlib.h>
#include "bitmap.h"
int main()
{
	char str[100];
	func ft[]={bitOn,bitOff,bitStatus};
	bitmap* b;
	int size,i,bit,x,N=0;
	while(N<1)
	{
		printf("Please, enter array size :)\n");
		scanf("%d",&N);
	}
	if(N%32)
		size=1;
	size+=N/32;
	b=create(N);
	if(!x)
	{	
		printf("BitMap can't be allocated :(");
		return 0;
	}
	while(1)
    {
        printf("Choose option:\n1->Turn on bit.\n2->Turn off bit.\n3->Bit status.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
	        case 1:
	            printf("Enter you're choosen bit\n");
	            scanf("%d",&bit);
	            if(ft[0](b,bit)<0)/*bitOn(b,bit)<0)*/
	            {
	                printf("Illegal bit!");
	            }
	            for(i=1;i<=size;i++)
	            {
	            	Int2Bin(b->arr[size-i],str);
	            	printf("%s",str);
	            }
	            break;
	        case 2:
	            printf("Enter you're choosen bit\n");
	            scanf("%d",&bit);
	            if(ft[1](b,bit)<0)/*bitOff(b,bit)<0*/
	            {
	                printf("Illegal bit!");
	            }
	            for(i=1;i<=size;i++)
	            {
	            	Int2Bin(b->arr[size-i],str);
	            	printf("%s",str);
	            }
	            break;
	        case 3:
	            printf("Enter you're choosen bit\n");
	            scanf("%d",&bit);
	            i=ft[2](b,bit);/*bitStatus(b,bit);*/
	            if(i<0)
	            {
	                printf("Illegal bit!");
	            }
	            printf("Bit Status: %d\n",i);
	            break;
	        default:
	        	return 0;
		}
	}
	return 0;
}
