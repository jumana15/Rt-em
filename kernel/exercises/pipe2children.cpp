#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;

void pipeFunc()
{
	int status,pipefd[2];/*input/output*/
	int x=pipe(pipefd);
	pid_t pid1,pid2;
	if(x==-1)
	{
		throw string("Failed to Pipe!");
	}
	if(((pid1=fork())<0)||((pid2=fork())<0))
	{
		throw string("Failed to Fork!");
	}
	if(!pid1)
	{	
		close(STDOUT_FILENO);//standard output
		close(pipefd[0]);//input-read
		dup2(pipefd[1],STDOUT_FILENO);//output-write
		close(pipefd[1]);
		execl("/bin/ls", "/bin/ls", "-l", NULL);
	}
	if(!pid2)
	{
		close(STDIN_FILENO);
		close(pipefd[1]);
		dup2(pipefd[0],STDIN_FILENO);
		close(pipefd[0]);
		execl("/usr/bin/wc", "/usr/bin/wc", "-l", NULL);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	wait(NULL);
	wait(NULL);
}

int main()
{
	try
	{
		pipeFunc();
	}
	catch(string s)
	{
		cout<<s<<endl;
	}
	cout<<"Done!"<<endl;
	return 0;
}