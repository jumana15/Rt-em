#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "operation.h"

int main()
{
	unsigned char c=171,x=170,y=167,i=10,j=27,value=1;
	unsigned int x1=170;
	int n=3,p=6,r=3;
	printf("Invert Function:\n");
	invert(c);
	printf("Rotate Function:\n");
    	rotate(y,r);
    	printf("SetBits Function:\n");
    	setbits(x,p,n,y);
   	printf("SetBits Value Function:\n");
    	setbitsV(x1,i,j,value);

	/*while(1)
    {
        printf("Choose an option:\n1->Invert.\n2->Rotate.\n3->SetBits.\n4->SetBits by value.\nElse->stop.\n");
        scanf("%hh",&x);
        switch(x)
        {
	        case 1:
                printf("Enter a number:\n");
                scanf("%u",&c);
                invert(c);
                break;
            case 2:
                printf("Enter a number:\n");
                scanf("%hhu",&c);
                printf("Enter rotates number:\n");
                scanf("%d",&n);
                if(n>0)
                    rotate(c,n);
                break;
            case 3:
                printf("Enter the first number:\n");
                scanf("%8u",&x);
                printf("Enter the second number:\n");
                scanf("%hu",&y);
                printf("Enter 2 bits number:\n");
                scanf("%d %d",&n,&p);
                if((p>n)&&(p<8)&&(n>=0))
                    setbits(x,p,n,y);
                else
                    printf("Illegal bits!");
                break;
            case 4:
                printf("Enter a number:\n");
                scanf("%u",&x1);
                printf("Enter a value:\n");
                scanf("%hhu",&y);
                printf("Enter 2 bits number:\n");
                scanf("%d %d",&n,&p);
                setbits(x,n,p,y);
                break;
            default:
	        	return 0;
        }
    }*/
	return 0;
}
