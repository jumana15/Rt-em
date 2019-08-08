#include<stdio.h>
#include <string.h>
char* string_copy(char* str1, char* str2)
{
	int i=0;
	for(i=0;str2[i]!='\0';i++)
	{
		str1[i]=str2[i];
	}
	/*for(i=0;str2[i]!='\0';str1[i]=str2[i],i++)*/
	str1[i]='\0';
	return str1;
}
char* string_cat(char* str1, char* str2)
{
	int i=0,l=strlen(str1);
	for(i=0;str2[i]!='\0';i++)/*for(i=0;str2[i]!='\0';str1[l+i]=str2[i],i++)*/
	{
		str1[l+i]=str2[i];
	}
	str1[i+l]='\0';
	return str1;
}
int string_compare(char* str1,char* str2)
{
	int i=0;
	while((str1[i]!='\0')&&(str2[i]!='\0'))
	{
		if(str1[i]!=str2[i])
			break;
		i++;
	}
	/*if((str1[i]=='\0')&&(str2[i]=='\0'))
	{
		return 0;
	}*/
	return str1[i]-str2[i];
}
int main()
{
	char str1[15]={"jumana"};
	char str2[15]={"rayan"};
	char str3[15]={"jumana"};
	
	printf("%d\n",string_compare(str1,str2));
	printf("%d\n",string_compare(str1,str3));
	printf("%d\n",string_compare(str2,str1));
	printf("%s\n",string_copy(str3,str2));
	printf("%s\n",string_cat(str1,str2));
	printf("%s\n",string_cat(str1,str3));
	return 0;
}
