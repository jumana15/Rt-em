#include<stdio.h>
#include<stdlib.h>
void b(void);
void a(int x)
{
	int *addr=&x;
	addr-=1;
	*addr=b;
	printf("Hi a!\n");
}
void b(void)
{
	printf("Hi b!\n");
	exit(1);
}
int main()
{
	int x=5;
	a(x);
	return 0;
}