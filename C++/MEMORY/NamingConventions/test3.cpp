#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memManager_t.h"
#include "memPool_t.h"
#include "memPage_t.h"

int main()
{
	size_t k,x=1;
	char buffer[4];
	char buffer2[100];
	char s[6][9];
	strcpy(s[0],"c");//char
	strcpy(s[1],"b");//bool
	strcpy(s[2],"iiii");//int
	strcpy(s[3],"llllllll");//long
	strcpy(s[4],"ffff");//float
	strcpy(s[5],"dddddddd");//double
	memPool m1;
	memManager m;
	return 0;
}