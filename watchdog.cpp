#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;

void watchDog()
{
	pid_t pid;
	int status,counter=0;
	char* c;
	while(1)
	{
		if((pid=fork())<0)
		{
			throw string("Failed to fork!");
		}
		if(pid)
		{
			wait(&status);
			if(WIFEXITED(status))
			{
				cout<<"The child died normaly :)"<<endl;
				break;
			}
			cout<<"The child died abnormaly!"<<endl;
		}
		else
		{
			if(counter<10)
			{
				c[0]='a';
			}
			return;
		}
		counter++;
	}

}

int main() 
{
	try
	{
		watchDog();
	}
	catch(string s)
	{
		cout<<s<<endl;
	}
	return 0;
}