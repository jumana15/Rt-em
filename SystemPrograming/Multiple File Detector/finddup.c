#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include "md5m.h"
#include "hash.h"
#include "init.h"

extern void checkDup(hashArr* h, char* str,char* ename)
{
    char* s=(char*)malloc(200*sizeof(char));
    unsigned char* c=(unsigned char*)malloc(MD5_DIGEST_LENGTH*sizeof(unsigned char));
    int flag;
    strcpy(s,str);
    strcat(s,ename);
    flag=md5Func(c,ename);
    if(!flag)            
        exit(1);   
    flag=insertHash(h,(void*)c,(void*)s);
    if(flag==2)
    {
        printf("Duplicate File:%s.\n",s);
    }
}

void findDupRec(hashArr* h,char *dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char str[200];
    if((dp = opendir(dir)) == NULL) 
    {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    strcpy(str,dir);
    while((entry = readdir(dp)) != NULL) 
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) 
        {
            /* Found a directory, but ignore . and .. */
            if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
                continue;
            /* Recurse at a new indent level */
            strcat(entry->d_name,"/");
            findDupRec(h,entry->d_name);
        }
        else 
        {
            checkDup(h,str,entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

int main()
{
    hashArr* h=NULL;
    char filename[500];/*="/home/sqrt11/Documents/";*/
    int flag=initFunc(&h,filename);
    if(!flag)
        exit(1);
    findDupRec(h,filename);
    /*forEachHash(h);*/
    destroyHash(h);
    return 0;
}