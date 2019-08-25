#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
void operationFunc(Tree t)
{
	printTree(t);
}
int main()
{
    int x,num,flag=1;
    Tree t;
    operationFunction op=operationFunc;
    while(1)
    {
        printf("Choose option:\n1->Create Array.\n2->Insert.\n3->Delete.\n4->Print.\n5->Destroy.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
            	printf("Enter a number:\n");
            	scanf("%d",&num);
                newTree(&t,num);
                break;
            case 2:
            	printf("Enter a number:\n");
          		scanf("%d",&num);
                insert(t,num);
                break;
            case 3:
            	printf("Enter a number:\n");
            	scanf("%d",&num);
                delete(t,num);
                break;
            case 4:
                walk(t,op,0);
                break;
            case 5:
                destroy(t);
                t=NULL;
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