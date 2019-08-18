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
	unsigned char y=0;
	int i=0, pow2=1;
	char2Bin(x,str);
	while(i<8)
    {
        if(x%2==0)
        y+=pow2;
        x/=2;
        pow2*=2;
        i++;
    }
    char2Bin(y,str2);
    printf("x = %s\n",str);
	printf("x inverted  = %s\n",str2);
}
void rotate(unsigned char x,unsigned int n)
{
	unsigned char s,str[9];
	int n2=n;
	unsigned char y=x;
	while(n2>0)
	{
		s=y%2;
		y/=2;
		y+=s*128;
		n2--;
	}
	char2Bin(x,str);
	printf("x = %s\n",str);
	char2Bin(y,str);
	printf("x rotated by %d = %s\n",n,str);

}
void setbits(unsigned char x,int p,int n,unsigned char y)
{
    unsigned char strX[9],strXY[9],strY[9];
	int s_y=y,i=0,dig=0,pow2=1;
	while(i<p-n)
	{
		dig+=(s_y%2)*pow2;
		pow2*=2;
		s_y/=2;
		i++;
	}
	char2Bin(x,strX);
    char2Bin(y,strY);
	strcpy((char*)strXY,(char*)strX);
    i=n;
    while(i<p)
	{
            strXY[7-i]=dig%2+'0';
            dig/=2;
            i++;
            /*strXY[7-i]=strY[i-n];*/
	}
	printf("x = %s\n",strX);
	printf("y = %s\n",strY);
	printf("setbits n = %d, p = %d gives x = %s\n",n,p,strXY);
}
void setbitsV(unsigned int w,int i,int j,unsigned char value)
{
    unsigned char strX[33],strY[33];
    int i1=i;
    if((j>31)||(i<0)||(i>j))
    {
        printf("Illegal Input");
        return;
    }
    Int2Bin(w,strX);
	strcpy((char*)strY,(char*)strX);
    while(i<=j)
	{
            strY[i++]=value+'0';
	}
	printf("x = %s\n",strX);
	printf("setbits i = %d, j = %d gives x = %s\n",i1,j,strY);
}
