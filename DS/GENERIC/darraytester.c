#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "darrayheader.h"

typedef struct
{
    int age;
    char name[15];

}person;

int cmpFunc(void* a,void* b)
{
    return (((person*)a)->age)-(((person*)b)->age);
}

void destroyFunc(void* p,void *context)
{
    fprintf((FILE*)context,"NAME: %s\tAGE: %d.\n",((person*)p)->name,((person*)p)->age);
    fflush((FILE*)context);
    free((person*)p);
}

void createArr(darray** arr)
{
    AdtStatus st;
    size_t size;
    printf("\nPlease, enter size:\n");
    scanf("%lu",&size);
    if(size>=1)
    {
        st=darrayCreate(arr,size);
        if(st)
        {
            printf("AllocationError!\n");
            exit(1);
        }
    }
    else
        printf("Size cannot be less than one !\n");
}

void addArr(darray* arr)
{
    AdtStatus st;
    int num;
    char name[15];
    person* item;
    printf("\nPlease Enter Name and Age:\n");
    scanf("%s%d",name,&num);
    if(num>0)
    {
        item=(person*)malloc(sizeof(person));
        if(item)
        {
            strcpy(item->name,name);
            item->age=num;
            st=darrayAdd(arr,(void*)item);
            if(st)
            {
                printf("AllocationError!\n");
            }
        }
        printf("The person is: %s Age:%d.\n",item->name,item->age);
    }
    else
        printf("Age can't be less than zero!");
}

void deleteArr(darray* arr)
{
    AdtStatus st;
    person* item;/*=(person*)malloc(sizeof(person));*/
    st=darrayDelete(arr,((void**)&item));
    if(st)
    {
        printf("AllocationError!\n");
    }
    else
    {
        printf("The deleted person is: %s Age:%d.\n",item->name,item->age);
        free(item);
    }
}

void setArr(darray* arr)
{
    int num;
    char name[15];
    size_t index;
    person* item;
    AdtStatus st;
    printf("\nPlease Enter Name, Age and Index:\n");
    scanf("%s%d%lu",name,&num,&index);
    if(num>0)
    {
        item=(person*)malloc(sizeof(person));
        strcpy(item->name,name);
        item->age=num;
        st=darraySet(arr,index,item);
        if(st)
        {
            printf("AllocationError!\n");
        }
    }
}

void getArr(darray* arr)
{
    person* item;
    AdtStatus st;
    size_t index;
    printf("\nPlease Enter an Index:\n");
    scanf("%lu",&index);
    /*item=(person*)malloc(sizeof(person));*/
    st=darrayGet(arr,index,((void**)&item));
    if(st)
    {
        printf("AllocationError!\n");
    }
    else
    {
        printf("Name:%s age:%d.\n",item->name,item->age);
    }
}

void itemsArr(darray* arr)
{
    int num;
    AdtStatus st=darrayItemsNum(arr,&num);
    if(st)
    {
        printf("AllocationError!\n");
    }
    else
    {
        printf("Number of Items =%d.\n",num);
    }
}

void sortArr(darray* arr,elementCompare c)
{
    AdtStatus st=darraySort(arr,c,7);
    if(st)
    {
        printf("AllocationError11!\n");
    }
}

void destroyArr(darray* arr,elementDestroy d,void* context)
{
    AdtStatus st=darrayDestroy(arr,d,(void*)context);
    if(st)
    {
        printf("AllocationError!\n");
    }
}

int main()
{
    FILE* context;
    char s[]="output.txt";
    int x,flag=1;
    darray *arr;
    elementDestroy d=destroyFunc;
    elementCompare c=cmpFunc;
    if((context=fopen(s,"w"))==NULL)
    {
        exit(1);
    }
    while(1)
    {
        printf("Choose option:\n1->Create Array.\n2->Add.\n3->Delete.\n4->Set.\n5->Get.\n6->Items Number.\n7->Sort.\n8->Destroy.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                createArr(&arr);
                break;
            case 2:
                if(arr)
                    addArr(arr);
                break;
            case 3:
                if(arr)
                    deleteArr(arr);
                break;
            case 4:
                if(arr)
                    setArr(arr);
                break;
            case 5:
                if(arr)
                    getArr(arr);
                break;
            case 6:
                if(arr)
                    itemsArr(arr);
                break;
            case 7:
                if(arr)
                    sortArr(arr,c);
                break;
            case 8:
                if(arr)
                    destroyArr(arr,d,context);
                break;
            default:
                flag=0;
                break;
        }
        if(!flag)
            break;
    }
    fclose(context);
    return 0;
}