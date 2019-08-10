#include<stdio.h>
#include<string.h>
void Int2Bin(unsigned int num,char* str)
{
	int j=0,i=0;
	char tmp;
	while(num>0)
	{
		str[i]=(char)(num%2+48);
		i++;
		num/=2;
	}
	str[i]='\0';
	while(j<(i-1-j))/*swap*/
	{
		tmp=str[j];
		str[j]=str[i-j-1];
		str[i-j-1]=tmp;
		j++;
	}
}
unsigned int Bin2Int(char* num)
{
	int i,d_num=0,pow2=1,len=strlen(num);
	for(i=len-1;i>=0;i--)
	{
		d_num+=pow2*(num[i]-48); /*'0'=48*/
		pow2*=2;
	}
	return d_num;

}
char* squeeze(char* s1,char* s2)
{
	int j,i=0,index=0,len2=strlen(s2);/*index-> string of the legal letters,index*/
	while(s1[i]!='\0')
	{
		for(j=0;j<len2;j++)
		{
			if(s2[j]==s1[i])
				break;
		}
		if(s2[j]=='\0') /*legal letter*/
		{
			s1[index]=s1[i];
			index++;
		}
		i++;
	}
	s1[index]='\0';
	return s1;


}
int Location(char* s1,char* s2)
{
	int i,j,len1=strlen(s1),len2=strlen(s2);
	for(i=0;i<len1-len2+1;i++)
	{
		if(s2[0]==s1[i])
		{
			for(j=1;j<len2;j++)
			{
				if(s2[j]!=s1[i+j])
				{
					break;
				}
			}
			if(j==len2)
				return i;
		}
	}
	return -1;
}
int main()
{
	char str[33],s1[7] ="ABCDEF",s2[3] ="CD",s3[4]="BKE",s4[7]="ABCDEF";
	unsigned int num;
	int num1,flag=1;
	int i;
	while(1)
	{
		printf("Please enter a number:\n");
		scanf("%d",&num1);
		if(num1<0)
			break;
		num=num1;
		Int2Bin(num,str);
		printf("Int=%d -> Bin=%s\n",num,str);
	}
	while(1)
	{
		printf("Please enter a string:\n");
		scanf("%s",str);
		for(i=0;str[i]!='\0';i++)
		{
			if((str[i]!='0')&&(str[i]!='1'))
            {
                flag=0;
				break;
            }
		}
		if(!flag)
        {
            break;
        }
		num=Bin2Int(str);
		printf("Int=%d -> Bin=%s\n",num,str);
	}
	printf("s1=%s s2=%s -> squeeze=",s1,s2);
	printf("%s\n",squeeze(s1,s2));
	strcpy(s1,s4);
	printf("s1=%s s2=%s -> squeeze=",s1,s3);
	printf("%s\n",squeeze(s1,s3));
	strcpy(s1,s4);
	printf("s1=%s s2=%s -> location=%d\n",s1,s2,Location(s1,s2));
	printf("s1=%s s2=%s -> location=%d\n",s1,s3,Location(s1,s3));
	return 0;
}
