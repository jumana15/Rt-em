#include<stdio.h>
#include "progB.h"
#include "libN.h"

void progAFunc()
{
	printf("progAFunc!\n");
}
int main()
{
	progAFunc();
	progBFunc();
	lib1Func();
	lib2Func();
	lib3Func();
	return 0;
}