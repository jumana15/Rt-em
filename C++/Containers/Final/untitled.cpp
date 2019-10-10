#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "container_t.h"

template<class T,class C> void testFunc(tContainer_t<T,C>* c)
{
	int* n;
	int x,y,flag=1;
	size_t z;
	while(1)
	{
		cout<<"press: 0-List Or 1-Vector."<<endl;
		cin>>x;
		
		cout<<"Choose option:\n1->isEmpty.\n2->elementsNumber.\n3->insertElement.\n4->getFirst.\n5->getLast.\n6->findElement.\n7->removeElement.\n8->removeElements.\n9->deleteElement.\n10->deleteElements.\n11->[].\nElse->break."<<endl;
		cin>>x;
		switch(x)
		{
			case 1:
			{
				cout<<"isEmpty: "<<c->isEmpty()<<"."<<endl;
				break;
			}
			case 2:
			{
				cout<<"elementsNumber: "<<c->elementsNumber()<<"."<<endl;
				break;
			}
			case 3:
			{
				cout<<"Enter a number:"<<endl;
				n=new int;
				cin>>*n;
				c->insertElement(n);
				break;
			}
			case 4:
			{
				cout<<"First: "<<*(c->getFirst())<<"."<<endl;
				break;
			}
			case 5:
			{
				cout<<"Last: "<<*(c->getLast())<<"."<<endl;
				break;

			}
			case 6:
			{
				cout<<"Enter a number:"<<endl;
				n=new int;
				cin>>*n;
				n=c->findElement(*n);
				if(!n)
				{
					cout<<"Not Found!"<<endl;
				}
				else
				{
					cout<<"Found! "<<*n<<"."<<endl;
				}
				delete n;
				break;
			}
			case 7:
			{
				cout<<"Enter a number:"<<endl;
				n=new int;
				cin>>*n;
				n=c->removeElement(*n);
				if(!n)
				{
					cout<<"Not Found!"<<endl;
				}
				else
				{
					cout<<"Removed! "<<*n<<"."<<endl;
				}
				delete n;
				break;
			}
			case 8:
			{
				c->removeElements();
				break;
			}
			case 9:
			{
				cout<<"Enter a number:"<<endl;
				n=new int;
				cin>>*n;
				c->deleteElement(*n);
				delete n;
				break;
			}
			case 10:
			{
				c->deleteElements();
				break;
			}
			case 11:
			{
				cout<<"Enter an Index:"<<endl;
				n=new int;
				cin>>z;
				try
				{
					n=c->operator[](z);//[z];
				}
				catch(string s)
				{
					cout<<s<<endl;
					break;
				}
				cout<<"c[index]= "<<*n<<endl;
				delete n;
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
}

int main()
{
	int x;
	switch(x)
	{
		case 0:
		{
			tContainer_t<int,list<int*> >* c = new tContainer_t<int,list<int*> > ();
			testFunc(c);
			break;		
		}
		default:
		{
			tContainer_t<int,vector<int*> >* c = new tContainer_t<int,vector<int*> > ();
			testFunc(c);
			break;
		}
	}
	return 0;
}
