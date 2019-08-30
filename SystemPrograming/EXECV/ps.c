#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>
#include<stdio.h>
 void function(char* str)
 {
 	int status;
 	char *cmd[10];
 	pid_t pid;
 	pid=fork();
 	if(pid)
 	{
 		printf("Parent\n");
 		printf("Parent pid=%u.\n",waitpid(pid, &status, 0));
 	}
 	else
 	{
 		printf("Son\n");
 		execv(str,cmd);
 	}
 }
 int main()
 {
 	char str[15];
 	printf("Enter file name:\n");
 	scanf("%s",str);
 	function(str);
 	return 0;
 }
