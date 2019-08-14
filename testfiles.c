#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "files.h"
int main()
{
    char* fname="input.txt";
    char* fname2="output.txt";
    FILE* ptr=NULL;
    FILE* ptr2=NULL;
    int size=0,lines=0;
    /*while(!ptr)
    {
    	printf("Please,enter file name:\n");
    	//scanf("%s",fname);
        ptr=fopen(fname,"r");
        ptr2=fopen(fname2,"w");
    }*/
    ptr=fopen(fname,"r");
    ptr2=fopen(fname2,"w");
    while(lines<1)
    {
        printf("Please,enter lines number:\n");
        scanf("%d",&lines);
    }
    while(size<1)
    {
        printf("Please,enter array size:\n");
        scanf("%d",&size);
    }
    char_counter(ptr,ptr2);
    PrintLastN(ptr,ptr2,lines);
    word_counter(ptr,ptr2,size);
    fclose(ptr2);
    fclose(ptr);
    return 0;
}
