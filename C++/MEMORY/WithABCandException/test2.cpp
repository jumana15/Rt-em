#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memManager_t.h"
#include "memPool_t.h"
#include "memPage_t.h"

int main()
{
	int x;
	size_t k,p,size;
	bool flag,f=1;
	memPool m1;
	char s[6][9];
	strcpy(s[0],"c");//char
	strcpy(s[1],"b");//bool
	strcpy(s[2],"iiii");//int
	strcpy(s[3],"llllllll");//long
	strcpy(s[4],"ffff");//float
	strcpy(s[5],"dddddddd");//double
	while(1)
	{
		cout<<"Choose option:\n1->Read.\n2->Write.\n3->Print.\nElse->stop."<<endl;
        scanf("%d",&x);
        k=0;
        switch(x)
        {
        	case 1:
        	{
        		cout<<"Enter a Position - (-1 for current position):"<<endl;
        		cin>>p;
        		cout<<"Enter a Size:"<<endl;
        		cin>>size;
        		char* buffer=new char[size]; 
        		if(p==-1)
        		{
        			flag=m1.read(buffer,&k,size);
        		}
        		else
        		{
        			flag=m1.read(buffer,&k,size,p);
        		}
        		if(flag)
        		{
        			cout<<"Read Function Succeed!"<<endl;
        		}
        		else
        		{
        			cout<<"Read Function Failed!"<<endl;
        		}
        		cout<<"k= "<<k<<"!"<<endl;
        		for(int i=0;i<k;i++)
						cout<<buffer[i];
				cout<<endl;
        		delete buffer;
        		break;
        	}
        	case 2:
        	{
        		cout<<"Enter a Position - (-1 for current position):"<<endl;
        		cin>>p;
        		cout<<"Enter a Size:"<<endl;
        		cin>>size;
        		char* buffer=new char[size+1]; 
        		cout<<"Enter a String:"<<endl;
        		cin>>buffer;
        		if(p==-1)
        		{
        			flag=m1.write(buffer,&k,size);
        		}
        		else
        		{
        			flag=m1.write(buffer,&k,size,p);
        		}
        		cout<<"k= "<<k<<"!"<<endl;
        		if(flag)
        		{
        			cout<<"Write Function Succeed!"<<endl;
        		}
        		else
        		{
        			cout<<"Write Function Failed!"<<endl;
        		}
        		delete buffer;
        		break;
        	}
        	case 3:
        	{
        		m1.print();
        		break;
        	}
        	default:
        	{
        		f=0;
        		break;
        	}
        }
        if(!f)
        {
        	break;
        }
	}
	return 0;
}