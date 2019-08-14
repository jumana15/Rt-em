#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "files.h"
void PrintLastN(FILE* ptr,FILE* output,int N)
{

    char c[512];
    unsigned int* arr=(unsigned int*)malloc(N*sizeof(unsigned int));
    int j,count=0,i=0;
    while((!feof(ptr))&&(ptr))
    {
        fgets(c,512,ptr);
        arr[i%N]=ftell(ptr);
        i++;
        count++;
    }
    if(count<N)
    {
        printf("N > file lines number!");
        return;
    }
    for(j=0; j<N; j++)
    {
        fseek(ptr,arr[(i+j)%N],SEEK_SET);
        fgets(c,512,ptr);
        if(c[strlen(c)-1]=='\n')
            c[strlen(c)-1]='\0';
        printf("%s\n", c);
        fprintf(output,"%s\n",c);
    }
}

void char_counter(FILE* ptr,FILE* output)
{
    char c;
    int i, char_array[256];
    for(i=0; i<256; i++)
        char_array[i]=0;
    while((c=getc(ptr))!= EOF)
        char_array[c]++;
    for(i=0; i<256; i++)
    {
        if((char_array[i]!=0)&&(((i>='A')&&(i<='Z'))||((i>='a')&&(i<='z'))))
        {
            fprintf(output,"%c	%d\n",i,char_array[i]);
            printf("%c	%d\n",i,char_array[i]);
        }
    }
}

stock* init_S(stock* s,int size)
{
    s=(stock*)malloc(sizeof(stock));
    if(s)
    {
        s->wCount=(wordOccurrences**)malloc(size*sizeof(wordOccurrences*));
        if(!s->wCount)
        {
            free(s);
            return NULL;
        }
        s->size=size;
        s->index=0;
    }
    return s;
}

int insert(stock* s,char* str)
{
    int i;
    char* p;
    wordOccurrences** ip;
    for(i=0; i<s->index; i++)
    {
        if(!strcmp(s->wCount[i]->str,str))
        {
            s->wCount[i]->count++;
            return 1;
        }
    }
    if(s->index>=s->size)
    {
        ip=(wordOccurrences**)realloc(s->wCount,(s->size*2)*sizeof(wordOccurrences*));
        if(!ip)
            return 0;
        s->size*=2;
        s->wCount=ip;
    }
    s->wCount[s->index]->str=(char*)malloc(70*sizeof(char));
    strcpy(s->wCount[s->index]->str,str);
    s->wCount[s->index]->count=1;
    s->index++;
    return 1;
}

int word_counter(FILE* input,FILE* output,int size)
{
    char str[70],str1[70];
    int flag,flag2,i=0,co=0;
    stock* s=init_S(s,size);
    if(!s)
        return 0;
    while (fscanf(input, "%s", str)!=EOF)
    {
        fscanf(input,"%s",str1);
        flag=insert(s,str);
        flag2=insert(s,str1);
        if((!flag)||(!flag2))
        {
            printf("Can't be added");
            return 0;

        }
    }
    for(i=0; i<s->index; i++)
    {
        fprintf(output,"%s      %d",s->wCount[i]->str,s->wCount[i]->count);
        printf("%s      %d",s->wCount[i]->str,s->wCount[i]->count);

    }
    return 1;
}

