#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <linux/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include "mq.h"

int main()
{
	int fd, ret;
	char* s="/dev/mq0";
	fd=open(s,O_RDWR);  
	if(fd==-1) {
		fprintf(stderr, "open error\n"); 
		return 1;
	}

	struct message_struct m;
	char* str=(char*)malloc(4096);
	m.buf=str;
	m.size=strlen(str);
	ret=ioctl(fd,MQ_RECV_MESSAGE,&m);
	if(ret==-1) {
		fprintf(stderr, "ioctl error\n"); 
		return 1;
	}
	printf("the message is %s\n", m.buf);

	ret=close(fd);
	if(ret==-1) {
		fprintf(stderr, "close error\n"); 
		return 1;
	}

	return 0;
}
