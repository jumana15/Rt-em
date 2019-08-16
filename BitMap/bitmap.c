#include<stdio.h>
#include<stdlib.h>
#include "bitmap.h"
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
	return 1;

}
int bitOff(bitmap* b,int bit)
{
	char*s;
	int flag=1;
	if(bit>=b->N)
		return -1;
	flag<<=bit%32;
	flag=~flag;
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
