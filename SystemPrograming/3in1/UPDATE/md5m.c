#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <linux/limits.h>
#include <libgen.h>
#include <openssl/md5.h>
#include "md5m.h"
int md5Func(unsigned char* c,char* filename)
{
	/*char filename2[PATH_MAX+1];
	strcpy(filename2,filename);
	char* d=dirname(filename2);
	char* fn=basename(filename);
	chdir(d);*/
	/*if(pthread_mutex_lock(&mutexMD5)!=0)
		printf(":@ :@ :@\n");
    */FILE *inFile = fopen (filename, "rb");
    MD5_CTX mdContext;
    int i;
    int bytes;
    unsigned char data[128];
    if (!inFile) 
    {
        printf ("%s can't be opened.\n", filename);
    	pthread_mutex_unlock(&mutexMD5);
        return 0;
    }
    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 128, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);
    fclose (inFile);
    /*for(i=0;i<MD5_DIGEST_LENGTH;i++)
    	printf("%02x",c[i]);
	printf("\nC \n");*/
	/*pthread_mutex_unlock(&mutexMD5);*/
	/*sem_post(&semMD5);
    */return 1;
}