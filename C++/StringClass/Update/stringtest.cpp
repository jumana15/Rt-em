#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stringt.h"

int main()
{
    String s("check");
    String s3("abc"),s4("xyz"),s5("a"),s7("we"),s8("try");
    String s1("here!");
    char str[15],str2[15];
    int x,flag=1;
    s.upperCase();
    s.print();
    s.lowerCase();
    s.print();
    s.prependChar("String");
    s.print();
    s.prependString(s1);
    s.print();
    s7+=s8;
    s7.print();
    s5+=("clean!");
    s5.print();
    printf("%d\n",s3<s4);
    printf("%d\n",s3>s4);
    printf("%d\n",s3>=s4);
    printf("%d\n",s3<=s4);
    printf("%d\n",s3==s4);
    printf("%d\n",s3!=s4);
    printf("contain -%d\n",s3.contain(s5));
    printf("contain -%d\n",s4.contain(s5));
    s3[2]='a';
    s3.print();
    s.print();
    printf("%c\n",s[7]);
	cout<<s;
	cin>>s5;
	cout<<s5;

    /*while(1)
    {
        printf("Choose option:\n1->Default Constructor.\n2->Constructor From (Char*).\n3->Copy Constructor.\n4->""="".\n5->Length.\n6->Set String.\n7->Get String.\n8->Compare.\n9->Destructor.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
	        case 1:
	        {
	            String s1;
	            s1.print();
	            //s1.~String();
	            break;
	        }
	        case 2:
			{
	            printf("\nPlease Enter your (char*) String:\n");
	            scanf("%s",str);
	            String s2(str);
	            s2.print();
	            //s2.~String();
	            break;
	        }
	        case 3:
			{        
	            printf("\nPlease Enter your String:\n");
	            scanf("%s",str);
	            String s3(str);
	            s3.print();
	            String s9(s3);
	            s9.print();
	            //s3.~String();
	            //s9.~String();
	            break;
			}
	        case 4:
	        {
	            printf("\nPlease Enter your String:\n");
	            scanf("%s",str);
	            s4.setString(str);
	            s4.print();
	            printf("S before:\t");
	            s.print();
	            s=s4;
	            printf("S after:\t");
	            s.print();
	            break;
	        }
	        case 5:
	        {
	            printf("\nPlease Enter your String:\n");
	            scanf("%s",str);
	            s5.setString(str);
	            printf("Length=%lu.\n",s5.length());
	            break;
	        }
	        case 6:
	        {
	            printf("\nPlease Enter your String:\n");
	            scanf("%s",str);
	            printf("Old S:\t");
	            s.print();
	            s.setString((const char*)str);
	            printf("New S:\t");
	            s.print();
	            break;
	        }
	        case 7:
	        {
	            printf("String= %s.\n",(char*)s.getString());
	            break;
	        }
	        case 8:
	        {
	            printf("\nPlease your First String:\n");
	            scanf("%s",str);
	            printf("\nPlease your Second String:\n");
	            scanf("%s",str2);
	            s7.setString(str);
	            s8.setString(str2);
	            printf("%s %s\n",s7.getString(),s8.getString());
	            s7.print();
	            s8.print();
	            printf("Compare=%d.\n",s7.compare(s8));
	            break;
	        }
	        case 9:
	        {
	            s.~String();
	            s4.~String();
	            s5.~String();
	            s7.~String();
	            s8.~String();
	        }
	        default:
	        {
	            flag=0;
	            break;
	        }
    	}
        if(!flag)
            break;
    }*/
    return 0;
}