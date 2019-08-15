#include<stdio.h>
#include<stdlib.h>
typedef struct
{
	int N;
	int* arr;
}bitmap;

typedef int (*func)(bitmap*,int);

void Int2Bin(int num,char* str)
{
	int j=0,i=0;
	char tmp;
	while(num>0)
	{
		str[i]=(char)(num%2+48);
		i++;
		num/=2;
	}
	while(i<32)
		str[i++]='0';
	str[i]='\0';
	while(j<(i-1-j))/*swap*/
	{
		tmp=str[j];
		str[j]=str[i-j-1];
		str[i-j-1]=tmp;
		j++;
	}
}

int bitOn(bitmap* b,int bit)
{
	int flag=1;
	if(bit>=b->N)
		return -1;
	flag<<=bit%32;
	b->arr[bit/32]|=flag;
	printf("bit=%d\n",b->arr[bit/32]);
	return 1;

}
int bitOff(bitmap* b,int bit)
{
	int flag=~1;
	if(bit>=b->N)
		return -1;
	flag<<=bit%32;
	b->arr[bit/32]&=flag;
	return 1;

}

int bitStatus (bitmap* b,int bit)
{
	int flag=1;
	if(bit>=b->N)
		return -1;
	flag<<=bit%32;
	flag&=b->arr[bit/32];
	flag>>=(bit%32);
	return flag;
}

bitmap* create(int N)
{
	bitmap* b;
	int i,size=0; 
	b=(bitmap*)malloc(sizeof(bitmap));
	if(!b)
		return b;
	if(N%32)
		size=1;
	size+=N/32;
	b->N=N;
	b->arr=(int*)malloc(size*sizeof(int));
	if(!b->arr)
	{
		free(b);
		return NULL;
	}
	for(i=0;i<size;i++)
		b->arr[i]=0;
	return b;
}

void destroy(bitmap* b)
{	
	if(!b)
		return;
	if(b->arr)
		free(b->arr);
	free(b);
}
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
	            if(bitOn(b,bit)<0)/*ft[0](b,bit))*/
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
	            if(bitOff(b,bit)<0)/*ft[0](b,bit))*/
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
	            i=bitStatus(b,bit);
	            if(i<0)/*ft[0](b,bit))*/
	            {
	                printf("Illegal bit!");
	            }
	            printf("Bit Status: %d",i);
	            break;
	        case -5:
	        	break;
		}
	}










	return 0;
}
