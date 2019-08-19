#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "operation.h"

void Int2Bin(unsigned int num,unsigned char* str)
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

void char2Bin(unsigned char c,unsigned char* str)
{
	int j=0,i=0;
	char tmp;
	while(c>0)
	{
		str[i++]=(char)(c%2+'0');
		c/=2;
	}
	while(i<8)
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
void invert(unsigned char x)
{
	unsigned char str[9],str2[9];
	unsigned char y=x;
	int i=0;
    for(i=0;i<8;i++)  
    	y=(y^(1<<i));
    char2Bin(x,str);
    char2Bin(y,str2);
    printf("x = %s\n",str);
	printf("x inverted  = %s\n",str2);
}
void rotate(unsigned char x,unsigned int n)
{
	unsigned char strX[9],strY[9];
	int y=x;
	n%=8;
	y=(x>>n)|(x<<(8-n));
	char2Bin(x,strX);
	char2Bin(y,strY);
	printf("x = %s\n",strX);
	char2Bin(y,strY);
	printf("x rotated by %d = %s\n",n,strY);

}
void setbits(unsigned char x,int p,int n,unsigned char y)
{
	unsigned char strX[9],strXY[9],strY[9];
	int i,y1=y,x1=x;
	y1<<=(8-p+n); 
	y1>>=(8-p);
	for(i=n;i<p;i++)
	{
		x1&=(~(1<<i));
	}
	y1|=x1;
	char2Bin(x,strX);
    char2Bin(y,strY);
    char2Bin(y1,strXY);
	printf("x = %s\n",strX);
	printf("y = %s\n",strY);
	printf("setbits n = %d, p = %d gives x = %s\n",n,p,strXY);
}
void setbitsV(unsigned int x,int i,int j,unsigned char value)
{
    unsigned char strX[33],strY[33];
    int i1,x1=x;
    if((j>31)||(i<0)||(i>j))
    {
        printf("Illegal Input");
        return;
    }
    if(!value)
    {
		for(i1=i;i1<=j;i1++)
		{
			x1&=(~(1<<i1));
		}
	}
	else
	{
		for(i1=i;i1<=j;i1++)
		{
			x1|=(1<<i1);
		}
	}
	Int2Bin(x,strX);
    Int2Bin(x1,strY);
	printf("x = %s\n",strX);
	printf("y = %s\n",strY);
	printf("setbits i = %d, j = %d  vlaue= %d gives x = %s\n",i,j,value,strY);
}
