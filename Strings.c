#include<stdio.h>
#include<string.h>
int reverse(int num)
{
	int r_num=0;
	while(num>0)
	{
		r_num=r_num*10+num%10;
		num/=10;
	}
	return r_num;
}
void Int2Bin(unsigned int num,char* str)
{
	int count=0;
	int b_num=0;
	while(num>0)
	{
		b_num=b_num*10+num%2;
		num/=2;
		if(!b_num)
			count++;
	}
	b_num=reverse(b_num);
	while(count)
	{
		count--;
		b_num*=10;
	}

	sprintf(str, "%d",b_num);
	printf("%s",str);
}
unsigned int Bin2Int(char* num)
{
	int i,d_num=0,pow2=1,len=strlen(num);
	for(i=len-1;i>=0;i--)
	{	/*I can use atoi*/
		d_num+=pow2*(num[i]-48); /*'0'=48*/
		pow2*=2;
	}
	return d_num;

}
char* squeeze(char* s1,char* s2)
{
	int j,flag=1,i=0,len2=strlen(s2);
	while(s1[i]!='\0')
	{
		for(j=0;j<len2;j++)
		{
			if(s1[i]==s2[j])
			{
				flag=0;
				s1[i]='\0';
				strcat(s1,&s1[i+1]);
				i--;
				break;
			}

		}
        i++;
	}
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
