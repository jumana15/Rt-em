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
	memPool m1,m2;
	for(int i=0;i<10;i++)
	{
		m1.write((void*)s[0],&k,sizeof(char));
		m1.write((void*)s[1],&k,sizeof(bool));
		m1.write((void*)s[2],&k,sizeof(int));
		m1.write((void*)s[3],&k,sizeof(long));
		m1.write((void*)s[4],&k,sizeof(float));
		m1.write((void*)s[5],&k,sizeof(double));
	}
	m1.write((void*)s[0],&k,sizeof(char));
	m1.print();
	for(int i=0;i<10;i++)
	{
		m2.write((void*)s[0],&k,sizeof(char),x-1);
		x=m2.memManager::getActualSize();
		m2.write((void*)s[1],&k,sizeof(bool),x-1);
		x=m2.memManager::getActualSize();
		m2.write((void*)s[2],&k,sizeof(int),x-1);
		x=m2.memManager::getActualSize();
		m2.write((void*)s[3],&k,sizeof(long),x-1);
		x=m2.memManager::getActualSize();
		m2.write((void*)s[4],&k,sizeof(float),x-1);
		x=m2.memManager::getActualSize();
		m2.write((void*)s[5],&k,sizeof(double),x-1);
		x=m2.memManager::getActualSize();
	}
	m2.print();
	for(int i=0;i<66;i++)
	{
		m1.read(buffer,&k,4,4*i);
		cout<<i<<" :";
		for(int i=0;i<4;i++)
			cout<<buffer[i];
		cout<<endl;
		strcpy(buffer,"   \0");	
	}
	m1.read(buffer2,&k,100,3);
	for(int i=0;i<100;i++)
		cout<<buffer2[i]<<" ";
	m1.write((void*)"0000000000000000000000000",&k,20,3);
	m1.print();
	return 0;
}