#include<stdio.h>
#include<stdlib.h>
#include "darray_int.h"
int main()
{
    int x,num,flag=1;
    darray *arr;
    int* item;
    AdtStatus st;
    int size,index;
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
                printf("\nPlease Enter a number:\n");
                scanf("%d",&num);
                st=darrayAdd(arr,num);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 3:
                st=darrayDelete(arr,item);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("The deleted item is: %d.\n",*item);
                }
                break;
            case 4:
                printf("\nPlease Enter an Index and an Item:\n");
                scanf("%d%d",&index,&num);
                st=darraySet(arr,index,num);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 5:
                 printf("\nPlease Enter an Index:\n");
                scanf("%d",&index);
                st=darrayGet(arr,index,item);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("Item=%d.\n",*item);
                }
                break;
            case 6:
                st=darrayItemsNum(arr,item);
                 if(st)
                {
                    printf("AllocationError!\n");
                }
                else
                {
                    printf("Number of Items =%d.\n",*item);
                }
                break;
            case 7:
                st=darraySort(arr,arr->index);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 8:
                st=darrayDestroy(arr);
                if(st)
                {
                    printf("AllocationError!\n");
                }
                break;
            case 9:
                for(num=0;num<arr->index;num++)
                {
                    printf("%d\t",arr->arr[num]);
                }
                printf("\n");
                break;
            case 10:
                printf("%d\n",arr->size);
                break;
            default:
                flag=0;
                break;
        }
        if(!flag)
            break;
    }
    darrayDestroy(arr);
    return 0;
}
