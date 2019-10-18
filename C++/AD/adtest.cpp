#include "ad.h"

int main()
{
    int x,size,flag=1;
    float begin,end;
    string subject;
    Meeting* m;
    AD ad;
    while(1)
    {
        cout<<"Choose option:\n1->Create meeting.\n2->Insert.\n3->Remove.\n4->Find.\n5->Clean AD.\n6->Print AD.\n7->Load Meetings From File.\nElse->stop."<<endl;
        cin>>x;
        switch(x)
        {
	        case 1:
	        {
	            cout<<"Please Enter begin, end and subject."<<endl;
	            cin>>begin;
	            cin>>end;
	            cin>>subject;
	            try
	            {
	            	m=new Meeting(begin,end,subject);
	            	m->printMeeting();
	            }
	            catch(string s)
	            {
	            	cout<<s<<endl;
	            	break;
	            }
	            break;
	        }
	        case 2:
	        {
	        	cout<<"Please Enter begin, end and subject."<<endl;
	            cin>>begin;
	            cin>>end;
	            cin>>subject;
	            try
	            {
	            	m=new Meeting(begin,end,subject);
	            	if(!ad.insertMeeting(m))
	            	{
	                	cout<<"Meeting can't be added :(."<<endl;
	            	}
	            }
	            catch(string s)
	            {
	            	cout<<s<<endl;
	            	break;
	            }
	            break;
	        }
	        case 3:
	        {
	            cout<<"Enter meeting time: "<<endl;
	            cin>>begin;
	           	m=ad.removeMeeting(begin);
	            if(!m)
	            {
	            	cout<<"Not Exist"<<endl;
	            }
	            else
	            {
	            	m->printMeeting();
	            	delete m;
	            }
	            break;
	        }
	        case 4:
	        {
	        	cout<<"Enter meeting time: "<<endl;
	            cin>>begin;
	           	m=ad.findMeeting(begin);
	            if(!m)
	            {
	            	cout<<"Not Exist"<<endl;
	            }
	            else
	            {
	            	m->printMeeting();
	            }
	            break;
	        }
	        case 5:
	        {
	        	ad.cleanAD();
	            break;
	        }
	        case 6:
	        {
	        	ad.printMap();
	            break;
	        }
			case 7:
			{
	            break;
			}
			default:
			{
				flag=0;
				break;
			}
        }
        if(!flag)
            break;
    }
    //StorewritingFile(list);
    return 0;
}