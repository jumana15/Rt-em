#include<stdio.h>
#include<string.h>
#include "pack.h"
int compress1(unsigned char* s)
{
	unsigned char a,b;
	int i=0,j=0,len=strlen((char*)s);
	if(len<1)
			return 0;
	while(i<len)
	{		
			a=(s[i]-'a')<<4;
			if(s[i+1]=='\0')
			{
				s[j++]=a;
				break;
			}
			else
			{
				b=s[i+1]-'a';	
				s[j++]=a|b;
			}
			i+=2;
	}
	return len;
}
int compress2(unsigned char* s)
{
	int i=0,j=0,len=strlen((char*)s);
	union letters l;
	if(len<1)
			return 0;
	while(i<len)
	{		
			l.d.a=(s[i]-'a');
			if(s[i+1]=='\0')
			{
				l.d.b=0;
				s[j++]=l.c;
				break;
			}
			else
			{
				l.d.b=s[i+1]-'a';
				s[j++]=l.c;
			}
			i+=2;
	}
	return len;
}
