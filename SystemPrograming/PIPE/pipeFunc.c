
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>
#include<stdio.h>
pipeFunc()
{
	int status,pipefd[2];/*input/output*/
	int x=pipe(pipefd);
	char str[15];
	pid_t pid;
	if(x==-1)
	{
		printf("Pipe Fail!");
		return 0;
	}
	pid=fork();
	if(pid)
	{	
		write(pipefd[1],"Hi",15);
		waitpid(pid, &status, 0);
		read(pipefd[0],str,15);
		printf("Son:%s.\n",str);
	}
	else
	{
		read(pipefd[0],str,15);
		printf("Parent:%s.\n",str);
		write(pipefd[1],"Bye",15);
	}
	close(pipefd[1]);
	close(pipefd[0]);
}
int main()
{
	pipeFunc();
	return 0;
}
