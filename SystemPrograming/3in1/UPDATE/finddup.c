#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <limits.h>
#include <sys/param.h>
#include <pthread.h> 
#include <semaphore.h> 

#include "md5m.h"
#include "hash.h"
#include "init.h"
#include "wqueue.h"
#include "finddup.h"

size_t co;
struct hashStruct{
    hashArr* h;
    char item[PATH_MAX+1];
    buffer_t* buffer;
};

void createHS(hashStruct** hs,size_t hashSize,size_t bufferSize)
{
	co=0;
    pthread_mutex_init(&mutexMD5, NULL);
    sem_init(&semMD5,0,1);
	*hs=(hashStruct*)malloc(sizeof(hashStruct));
	if(!(*hs))
		exit(1);
	initFunc(&((*hs)->h),(*hs)->item);
	createQueue(&((*hs)->buffer),bufferSize);
}

void* breakPoint(void* hs)
{
	int i;
	char* b;
	for(i=0;i<4;i++)
	{
		b=(char*)malloc(3*sizeof(char));
		if(!b)
			exit(1);
		strcpy(b,"-1");
		push(((hashStruct*)hs)->buffer,b);
	}
}

void destroyHS(hashStruct* hs)
{
    if(!hs)
        return;
    destroyHash(hs->h);
    destroyQueue(hs->buffer);
    free(hs);
    sem_destroy(&semMD5);
}

void* checkDup(void* hs)/*hashArr* h,char* ename)*/
{	
	char* ename;
    unsigned char* c;
    int flag;
    while(1)
    {
		flag=pop(((hashStruct*)hs)->buffer,(void**)(&ename));
	    if(!flag)
	    { 
	        exit(1);
	    }
	    if(strcmp(ename,"-1")==0)
	    	return;
	    /*pthread_mutex_lock(&mutexMD5);
	    sem_wait(&semMD5);
	    */if((c=(unsigned char*)malloc(MD5_DIGEST_LENGTH*sizeof(unsigned char)))==NULL)
	    	exit(1);
		flag=md5Func(c,ename);
		/*pthread_mutex_unlock(&mutexMD5);
	    */if(!flag) 
	    {
	    	printf("MD5Exit\n");
	    	exit(1);
	    	
	    }        
	    flag=insertHash(((hashStruct*)hs)->h,(void*)c,(void*)ename);
	    if(flag==2)
	    {
	    	printf("Number of Duplicates:%lu\n",++co);
	        printf("Duplicate File:%s.\n\n",ename);	
	    }
	}
	return;
}

void* findDupRec(void* hs)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char* item;
    char* actualpath;
    if((dp = opendir(((hashStruct*)hs)->item)) == NULL) 
    {
        fprintf(stderr,"cannot open directory: %s\n",((hashStruct*)hs)->item);
        return;
    }
    chdir(((hashStruct*)hs)->item);
    while((entry = readdir(dp)) != NULL) 
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) 
        {
            if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
                continue;
            strcpy(((hashStruct*)hs)->item,entry->d_name);
            findDupRec(hs);
        }
        else 
        {
        	actualpath=(char*)malloc((PATH_MAX+1)*sizeof(char));
        	if(!actualpath)
        		exit(1);
        	realpath(entry->d_name, actualpath);
        	push(((hashStruct*)hs)->buffer,actualpath);
   		}
   	}
    chdir("..");
    closedir(dp);
}

void createQueueThreads(hashStruct* hs,pthread_t* thr,size_t size)
{
	size_t i,status;
	for(i=0;i<size;i++)
	{
		status=pthread_create(&(thr[0]),NULL,findDupRec,(void*)hs);
		if(status)
	    	exit(1);
	}
}

void createHashThreads(hashStruct* hs,pthread_t* thr,size_t size)
{
	size_t i,status;
	for(i=0;i<size;i++)
	{
		status=pthread_create(&(thr[i]),NULL,checkDup,(void*)hs);
		if(status)
	    	exit(1);
	}
}

void joinQueueThreads(hashStruct* hs,pthread_t* thr,size_t size)
{
	size_t i,status;
	for(i=0;i<size;i++)
	{
		pthread_join(thr[i],NULL);
	}
	status=pthread_create(&(thr[0]),NULL,breakPoint,(void*)hs);
	if(status)
	    exit(1);
	pthread_join(thr[0],NULL);
}

void joinHashThreads(pthread_t* thr,size_t size)
{
	size_t i;
	for(i=0;i<size;i++)
	{
		pthread_join(thr[i],NULL);
	}
}

int main()
{
	int i,status;
	pthread_t thr[5];
    hashStruct* hs=NULL;
 	createHS(&hs,100000,100);
 	createQueueThreads(hs,thr,1);
 	createHashThreads(hs,thr+1,4);
 	joinQueueThreads(hs,thr,1);
 	joinHashThreads(thr+1,4);
	forEachHash(hs->h);
    destroyHS(hs);
    return 0;
}