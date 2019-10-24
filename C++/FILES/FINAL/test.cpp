#include "ascii.h"
#include "bin.h"
#include <string.h>

template<class T> void wTemplate(virtIO_t* vir,T t)
{
	try
	{
		(*vir)<<t;
	}
	catch(string s)
	{
		cout<<s;
	}
}

template<class T> void rTemplate(virtIO_t* vir,T& t)
{
	try
	{
		(*vir)>>t;
	}
	catch(string s)
	{
		cout<<s;
	}
}

int main()
{
	int x,y,i,flag=1;//f=0->ascii<->f=1->bin.
	float fl;
	void* str2=new char[100];
	string s;
	virtIO_t* vir;
	cout<<"Choose: 0-ASCII/1-BIN."<<endl;
	cin>>y;
	if(y==0)
	{
		vir=new asciiIO_t();
	}
	else
	{
		vir=new binIO_t(); 
	}
	while(1)
	{
		
		cout<<"1-OpenFile.\n2-CloseFile.\n3-GetPath.\n4-GetAccess.\n5-GetLength.\n6-GetPosition.\n7-GetStatus.\n8-Operator <<.\n9-Operator >>.\nElse-Exit."<<endl;
		cin>>x;
		switch(x)
		{
			case 1:
			{
				cout<<"Mode: 1-r / 2-r+ / 3-w/ 4-w+."<<endl;
				cin>>y;
				switch(y)
				{
					case 1:
					{
						s="r";
						break;
					}
					case 2:
					{
						s="r+";
						break;
					}
					case 3:
					{
						s="w";
						break;
					}
					case 4:
					{
						s="w+";
						break;
					}
				}
				try
				{
					vir->openFile("123.txt",s);
				}
				catch(string str)
				{
					cout<<str<<endl;
				}
				break;
			}
			case 2:
			{
				vir->closeFile();
				break;
			}
			case 3:
			{

				cout<<vir->getPath()<<endl;	
				break;
			}
			case 4:
			{
				cout<<vir->getAccess()<<endl;	
				break;
			}
			case 5:
			{
				cout<<vir->getLength()<<endl;	
				break;	
			}
			case 6:
			{
				cout<<vir->getPosition()<<endl;
				break;
			}
			case 7:
			{
				cout<<vir->getStatus()<<endl;	
				break;
			}
			case 8:
			{
				cout<<"Type: 1-int/2-float/3-void*."<<endl;
				cin>>y;
				switch(y)
				{
					case 1:
					{
						cout<<"Enter an Int:"<<endl;
						cin>>i;
						wTemplate<int>(vir,i);
						break;
					}
					case 2:
					{
						cout<<"Enter a Float:"<<endl;
						cin>>fl;
						wTemplate<float>(vir,fl);
						break;
					}
					case 3:
					{
						binIO_t* bin=dynamic_cast<binIO_t*>(vir);
						if(bin)
						{
							cout<<"Enter Number of Chars:"<<endl;
							cin>>i;
							cout<<"Enter a String:"<<endl;
							cin>>((char*)str2);
							try
							{
								(*bin)<<str2,i;
							}
							catch(string s)
							{
								cout<<s;
							}
						}
						break;
					}
				}
				break;
			}
			case 9:
			{
				cout<<"Type: 1-int/2-float/3-void*."<<endl;
				cin>>y;
				switch(y)
				{
					case 1:
					{
						rTemplate<int>(vir,i);
						cout<<"Int="<<i<<endl;
						break;
					}
					case 2:
					{
						rTemplate<float>(vir,fl);
						cout<<"Float="<<fl<<endl;
						break;
					}
					case 3:
					{
						binIO_t* bin=dynamic_cast<binIO_t*>(vir);
						if(bin)
						{
							cout<<"Enter Number of Chars:"<<endl;
							cin>>i;
							try
							{
								(*bin)>>str2,i;
								cout<<"String(Void*)="<<str2<<endl;
							}
							catch(string s)
							{
								cout<<s;
							}
						}
					
					}	break;
				}	
				break;
			}
			default:
			{
				flag=0;
			}
		}
		if(!flag)
		{
			break;
		}

	}

	return 0;
}