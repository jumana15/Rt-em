#include<stdio.h>
#include<stdlib.h>
#include "ad2.h"
int main()
{
    int size,x,room,flag=1;
    float begin,end;
    meeting_l *ip,*list=NULL;
    meeting* m;
    while(1)
    {
        printf("Choose option:\n1->Create AD.\n2->Create meeting.\n3->Insert.\n4->Remove.\n5->Find.\n6->Destroy AD.\n7->Print AD.\nElse->stop.\n");
        scanf("%d",&x);
        ip=NULL;
        switch(x)
        {
        case 1:
	    printf("\nPlease, enter size:\n");
	    scanf("%d",&size);
	    if(size>=1)
	    {
		list=createAD(size);
            	if(!list)
            	{
                	printf("AD can't be allocated :(");
                	return 0;
           	}
	    }
	    else
		printf("Size cannot be less than one !\n");
            break;
        case 2:
            printf("\nPlease Enter begin/end/room number\n");
            scanf("%f%f%d",&begin,&end,&room);
            if((begin>=0)&&(end>=0)&&(room>=0)&&(end>begin))
                m=createMeeting(begin,end,room);
            if(!m)
            {
                printf("Meeting can't be allocated :(");
            }
            break;
        case 3:
            if((m)&&(list))
                ip=sortMeeting(list,m);
            if(!ip)
            {
                printf("Meeting can't be added :(");
            }
            else
            {
                list=ip;
            }
            break;
        case 4:
            if(list)
            {
                printf("\nPlease, enter meeting time:\n");
                scanf("%f",&begin);
                if(begin>=0)
                    list=Mremove(list,begin);
            }
            else
                printf("\nThere's no AD\n");
            break;
        case 5:
            if(list)
            {
                printf("\nPlease, enter meeting time:\n");
                scanf("%f",&begin);
                if(begin>=0)
                    m=find(list,begin);
                if(m)
                    printf("Start:%f End:%f Room Number:%d\n",m->begin,m->end,m->room);
            }
            else
                printf("\nThere's no AD\n");
            break;
        case 6:
            list=destroyAD(list);
            break;
        case 7:
            if(list)
                printAD(list);
            else
                printf("\nThere's no AD\n");
            break;
        default:
            flag=0;
            break;
        }
        if(!flag)
            break;
    }
    list=destroyAD(list);
    return 0;
}
