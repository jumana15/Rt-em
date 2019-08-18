#include<stdio.h>
#include<string.h>
#include "pack.h"
int main()
{
	unsigned char s[100],s2[100];
	int i,len,len2;
	printf("Enter a string\n");
	scanf("%s",s);
	strcpy((char*)s2,(char*)s);
	len=compress1(s);
	len2=compress2(s2); 
	printf("len1=%d		len2=%d\n",len,len2);
	/*printf("\ncompress 1:\n");
	for(i=0;i<len;i++)
	{
		printf("\n%c %c ",(s[i]>>4)+'a',(s[i]&(15))+'a');
	}
	printf("\ncompress 2:\n");
	for(i=0;i<len;i++)
	{
		printf("%c %c ",((s2[i]&(15))+97),((s2[i]>>4)+97));
	}*/
	return 0;
}

