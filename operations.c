#include<stdio.h>
#include<string.h>
void char2Bin(char num,char* str)
{
	int j=0,i=0;
	char tmp;
	while(num>0)
	{
		str[i]=(char)(num%2+48);
		i++;
		num/=2;
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

void inverter(char c)
{
	char str[9];
	char y=0;
	int i, pow2=128;
	char2Bin(c,str);
	printf("x = %s\n",str);
	for(i=0;i<str[i]!='\0';i++)
	{
		if(str[i]=='0')
		{
			y=y+pow2;
		}
		pow2/=2;

	}
	printf("%d",y);
	char2Bin(y,str);
	printf("y = %s\n",str);
}
void rotate(char x,int n)
{
	char s,str[9];
	int c=n,y=x;
	while(n>0)
	{
		s=y%2;
		y/=2;
		y+=s*128;
	}
	char2Bin(x,str);
	printf("x = %s\n",str);
	char2Bin(y,str);
	printf("x rotated by %c = %s\n",c-'0',str);

}
void setbits(int x,int p,int n,int y)
{
	int s_y=y,i=0,dig=0,pow2=1,x1=0,counter=0;
	while(i<n)
	{
		dig+=(s_y%2)*pow2;
		pow*=2;
		s_y/=2;
	}
	while(x>0)
	{
		if()
		x1=
		counter
	}


}
int main()
{
	char c='a';
	rotate(c,3);
}