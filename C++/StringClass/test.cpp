#include<stdio.h>
#include<string.h>
#include "stringt.h"

int main()
{
    String s("check");
    char* str[15],str2[15];
    int flag=1;
    while(1)
    {
        printf("Choose option:\n1->Default Constructor.\n2->Constructor From (Char*).\n3->Copy Constructor.\n4->""="".\n5->Length.\n6->Set String.\n7->Get String.\n8->Compare.\n9->Destructor.\nElse->stop.\n");
        scanf("%d",&x);
        ip=NULL;
        switch(x)
        {
        case 1:
            String s1;
            s1.print();
            delete s1;
            break;
        case 2:
            printf("\nPlease Enter your (char*) String:\n");
            scanf("%s",str);
            String s2(str);
            s2.print();
            delete s2;
            break;
        case 3:
            printf("\nPlease Enter your String:\n");
            scanf("%s",str);
            String s3(str);
            s3.print();
            String s4(s3);
            s4.print();
            delete s3;
            delete s4;
            break;
        case 4:
            printf("\nPlease Enter your String:\n");
            scanf("%s",str);
            String s4(str);
            s4.print();
            printf("S before:\t");
            s.print();
            s=s4;
            printf("S after:\t");
            s.print();
            delete s4;
            break;
        case 5:
            printf("\nPlease Enter your String:\n");
            scanf("%s",str);
            String s5(str);
            printf("Length=%lu.\n",s5.length());
            delete s5;
            break;
        case 6:
            printf("\nPlease Enter your String:\n");
            scanf("%s",str);
            printf("Old S:\t");
            s.print();
            s.setString((const char*)str);
            printf("New S:\t");
            s.print();
            break;
        case 7:
            printf("String= %s.\n",(char*)s.getString());
            break;
        case 8:
            printf("\nPlease Enter 2 String:\n");
            scanf("%s%s",str,str2);
            String s7(str);
            String s8(str2);
            s7.print();
            s8.print();
            printf("Compare=%d.\n",s7.Compare(s8));
            delete s7;
            delete s8;
            break;
        case 9:
            s.~String();
        default:
            flag=0;
            break;
        }
        if(!flag)
            break;
    }
    return 0;
}
