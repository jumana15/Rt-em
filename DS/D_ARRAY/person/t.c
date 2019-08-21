#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "h.h"
typedef struct
{
    int age;
    char name[15];

}person;
int main()
{
    int x,num,flag=1;
    size_t num1;
    darray *arr;
    person* item;
    void* context;
    AdtStatus st;
    int size,index;
    char* name;
    elementDestroy d;
    while(1)
    {
        printf("Choose option:\n1->Create Array.\n2->Add.\n3->Delete.\n4->Set.\n5->Get.\n6->Items Number.\n7->Sort.\n8->Destroy.\n9->Print Array.\n10->Array Size.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
            printf("\nPlease, enter size:\n");
            scanf("%d",&size);
            if(size>=1)
            {
                st=darrayCreate(&arr,size);
                if(st)
                {
                        printf("AllocationError!\n");
                        return 0;
                }
            }
            else
                printf("Size cannot be less than one !\n");
            break;
            case 2:
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
                    printf("The deleted person is: %s Age:%d.\n",item->name,item->age);
                }
                else
                    printf("Age can't be less than zero!");
                break;
            case 3:
                item=(person*)malloc(sizeof(person));
                st=darrayDelete(arr,((void**)&item));
                if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("The deleted person is: %s Age:%d.\n",item->name,item->age);
                }
                break;
            case 4:
                printf("\nPlease Enter Name, Age and Index:\n");
                scanf("%s%d%d",name,&num,&index);
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
                break;
            case 5:
                 printf("\nPlease Enter an Index:\n");
                scanf("%d",&index);
                item=(person*)malloc(sizeof(person));
                st=darrayGet(arr,index,((void**)&item));
                if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("Name:%s age:%d.\n",item->name,item->age);
                }
                break;
            case 6:
                st=darrayItemsNum(arr,&num);
                 if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("Number of Items =%d.\n",num);
                }
                break;
            case 7:
                st=darraySort(arr,5);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 8:
                st=darrayDestroy(arr,d,context);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            /*case 9:
                for(num=0;num<arr->index;num++)
                {
                    printf("%d\t",arr->arr[num]);
                }
                printf("\n");
                break;
            case 10:
                printf("%d\n",arr->size);
                break;*/
            default:
                flag=0;
                break;
        }
        if(!flag)
            break;
    }
    darrayDestroy(arr,d,context);
    return 0;
}
