#include<stdio.h>
int Palindrome (int num)
{
	int num1=num;
	int p_num=0;
	while(num1>0)
	{
		p_num=p_num*10+num1%10;
		num1/=10;
	}
	if(p_num==num)
        return 1;
	return 0;
}
int is_ascending_order(int num)
{
	int tmp=num%10;
	num/=10;
	while(num>0)
	{
		if(tmp<=num%10)
			return 0;
		tmp=num%10;
		num/=10;
	}
	return 1;
}
int is_Perfect_number(int num)
{
	int sum=1,num1=num,i;
	for(i=2;i<num;i++)
		if((num%i)==0)
			sum+=i;
	if(sum==num)
		return 1;
	return 0;
}
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
int prime(int num)
{
	int i;
	for(i=2;i<(num/2)+1;i++)
		if((num%i)==0)
			return 0;
	return 1;
}
int main()
{
	int num;
	int x=0;
	int flag=0;
	while(!flag)
	{
		printf("Please, Enter a number: ");
		scanf("%d",&num);
		if(num>=0)
			flag=1;
	}
	x=Palindrome(num);
	if(x==1)
		printf("%d is a Palindrome number \n",num);
	else
		printf("%d isn't a Palindrome number \n",num);
	x=is_ascending_order(num);
	if(x==1)
		printf("%d is in ascending order \n",num);
	else
		printf("%d isn't in ascending order \n",num);
	x=is_Perfect_number(num);
	if(x==1)
		printf("%d is a Perfect number \n",num);
	else
		printf("%d isn't a Perfect number \n",num);
	x=reverse(num);
		printf("%d reversed number is %d \n",num,x);
	x=prime(num);
	if(x==1)
		printf("%d is a Prime \n",num);
	else
		printf("%d isn't a Prime \n",num);

	return 0;
}
