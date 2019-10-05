#include<stdio.h>
#include<string>
#include<iostream>

#include "building.h"
#include "street.h"
#include "city.h"

using namespace std;

int main()
{
	bool b;
	int x,y,z,flag=1;
	string str;
	Building_t<int>* bi=new Building_t<int>;
	Building_t<string>* bs=new Building_t<string>;
	Street_t<int,int>* si=new Street_t<int,int>;
	Street_t<string,string>* ss=new Street_t<string,string>;
	City_t<int,int,int> ci;
	City_t<string,string,string> cs;
	bi->setBuidingID(1);
	str="b1";
	bs->setBuidingID(str);
	si->setStreetID(1);
	str="s1";
	ss->setStreetID(str);
	ci.setCityID(1);
	str="c1";
	cs.setCityID(str);
	ss->AddBuilding2Street(bs);
	si->AddBuilding2Street(bi);
	cs.AddStreet(ss);
	ci.AddStreet(si);
	while(1)
	{
		cout<<"Choose option:\n1->Buiding.\n2->Street.\n3->City.\nElse->stop."<<endl;
        cin>>x;
        switch(x)
        {
        	case 1:
        	{
        		cout<<"press: 0-Number Or 1-String"<<endl;
        		cin>>b;
        		cout<<"Choose option:\n1->setID.\n2->getID.\nElse->break."<<endl;
        		cin>>y;
        		switch(y)
        		{
        			case 1:
        			{
        				if(b)
        				{
        					cout<<"Enter a String:"<<endl;
        					cin>>str;
        					bs->setBuidingID(str);
        				}
        				else
        				{

	        				cout<<"Enter an Integer:"<<endl;
	        				cin>>z;
	        				bi->setBuidingID(z);
        				}
        				break;
        			}
        			case 2:
        			{
        				if(b)
        				{
        					cout<<bs->getBuildingID()<<endl;
        				}
        				else
        				{
	        				cout<<bi->getBuildingID()<<endl;
        				}
        				break;
        			}
        			default:
                	{
                		break;
                	}
        		}
        		break;
        	}
        	case 2:
        	{
        		cout<<"press: 0-Number Or 1-String"<<endl;
        		cin>>b;
        		cout<<"Choose option:\n1->setID.\n2->getID.\n3->AddBuilding.\n4->getBuilding.\nElse->break."<<endl;
        		cin>>y;
        		switch(y)
        		{
        			case 1:
        			{
        				if(b)
        				{
        					cout<<"Enter a String:"<<endl;
        					cin>>str;
        					ss->setStreetID(str);
        				}
        				else
        				{

	        				cout<<"Enter an Integer:"<<endl;
	        				cin>>z;
	        				si->setStreetID(z);
        				}
        				break;
        			}
        			case 2:
        			{
        				if(b)
        				{
        					cout<<ss->getStreetID()<<endl;
        				}
        				else
        				{
	        				cout<<(int)si->getStreetID()<<endl;
        				}
        				break;
        			}
        			case 3:
        			{
        				if(b)
        				{
        					cout<<"Enter a String:"<<endl;
        					cin>>str;
        					Building_t<string>* s=new Building_t<string>;
        					s->setBuidingID(str);
        					ss->AddBuilding2Street(s);
        				}
        				else
        				{
	        				cout<<"Enter an Integer:"<<endl;
	        				cin>>z;
	        				Building_t<int>* i2=new Building_t<int>;
	        				i2->setBuidingID(z);
	        				si->AddBuilding2Street(i2);
        				}
        				break;
        			}
        			case 4:
        			{
        				cout<<"Enter an Index:"<<endl;
        				cin>>z;
        				if(b)
        				{
        					try
        					{
        						cout<<ss->getBuilding(z)->getBuildingID()<<endl;
        					}
        					catch(string s)
        					{
        						cout<<s<<endl;
        					}
        				}
        				else
        				{
        					try
        					{
        						cout<<si->getBuilding(z)->getBuildingID()<<endl;
        					}
        					catch(string s)
        					{
        						cout<<s<<endl;
        					}
        				}
        				break;
        			}
        			default:
                	{
                		break;
                	}
                }
                break;
        	}
        	case 3:
        	{
        		cout<<"press: 0-Number Or 1-String"<<endl;
        		cin>>b;
        		cout<<"Choose option:\n1->setID.\n2->getID.\n3->AddStreet.\n4->getStreet.\nElse->break."<<endl;
        		cin>>y;
        		switch(y)
        		{
        			case 1:
        			{
        				if(b)
        				{
        					cout<<"Enter a String:"<<endl;
        					cin>>str;
        					cs.setCityID(str);
        				}
        				else
        				{

	        				cout<<"Enter an Integer:"<<endl;
	        				cin>>z;
	        				ci.setCityID(z);
        				}
        				break;
        			}
        			case 2:
        			{
        				if(b)
        				{
        					cout<<cs.getCityID()<<endl;
        				}
        				else
        				{
	        				cout<<ci.getCityID()<<endl;
        				}
        				break;
        			}
        			case 3:
        			{
        				if(b)
        				{
        					cout<<"Enter a String:"<<endl;
        					cin>>str;
        					Street_t<string,string>* s=new Street_t<string,string>;
        					s->setStreetID(str);
        					cs.AddStreet(s);
        				}
        				else
        				{
	        				cout<<"Enter an Integer:"<<endl;
	        				cin>>z;
	        				Street_t<int,int>* i2=new Street_t<int,int>;
        					i2->setStreetID(z);
        					ci.AddStreet(i2);
        				}
        				break;
        			}
        			case 4:
        			{
        				cout<<"Enter an Index:"<<endl;
        				cin>>z;
        				if(b)
        				{
        					try
        					{
        						cout<<cs.getStreet(z)->getStreetID()<<endl;
        					}
        					catch(string s)
        					{
        						cout<<s<<endl;
        					}
        				}
        				else
        				{
        					try
        					{
        						cout<<(int)ci.getStreet(z)->getStreetID()<<endl;
        					}
        					catch(string s)
        					{
        						cout<<s<<endl;
        					}
        				}
        				break;
        			}
        			default:
                	{
                		break;
                	}
                }
                break;
        	}
        	default:
        	{
        		flag=0;
        		break;
        	}
        }
        if(!flag)
        {
        	break;
        }
	}
	return 0;
}