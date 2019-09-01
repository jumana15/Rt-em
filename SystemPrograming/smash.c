#include<stdio.h>
#include<stdlib.h>
void b(void)
{
	printf("b!\n");
	exit(1);
}
void a(void)
{
	
	int x=5;
	int *addr=&x;
	addr+=6;
	*(addr)=(int)b;
	printf("a!\n");
}
int main()
{
	a();
	return 0;
}