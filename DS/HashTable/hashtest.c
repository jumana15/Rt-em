#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"
size_t hashFunction(void* str)
{
	size_t h=5381;
	int c;
	while(c=(*(char*)str)++)
	{
		h=((h<<5)+h)+c;/*hash*33+c*/
	}
	return h;
}
void printFunction(void* key,void* value)
{
	printf("Key=%s\tValue=%s\n",(char*)key,(char*)value);
}
int cmpFunction(void* a,void* b)
{
	return strcmp((char*)a,(char*)b);
}
int main()
{
	hashFunc hf=hashFunction;
	printFunc pf=printFunction;
	cmpFunc cmpf=cmpFunction;
	int x,num,flag=1;
	size_t size;
	char *s1,*s2;
    hashArr* h;
    while(1)
    {
        printf("Choose option:\n1->Create Hash.\n2->Insert.\n3->Delete.\n4->Print.\n5->Destroy.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
            	printf("Enter a size\n");
            	if(size>0)
            	{
            		scanf("%lu",&size);
                	h=createHash(size);
           		}
            	else
            		printf("Size can't be less than zero!\n");
                break;
            case 2:
		s1=(char*)malloc(15*sizeof(char));
		s2=(char*)malloc(15*sizeof(char));
		if((s1)&&(s2))
		{
            		printf("Enter a key and a value:\n");
          		scanf("%s%s",s1,s2);
              		insertHash(h,(void*)s1,(void*)s2,hf,cmpf);
		}
                break;
            case 3:
		s1=(char*)malloc(15*sizeof(char));
		if(s1)
		{
            		printf("Enter a key:\n");
            		scanf("%s",s1);
                	deleteHash(h,(void*)s1,hf,cmpf);
		}
                break;
            case 4:
                forEachHash(h,pf);
                break;
            case 5:
                destroyHash(h);
                /*h=NULL;*/
                break;
            default:
                flag=0;
                break;
        }
        if(!flag)
            break;
    }
    return 0;
}
