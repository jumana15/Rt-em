#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <limits.h>
#include <sys/param.h>
#include "md5m.h"
#include "hash.h"
#include "init.h"

extern void checkDup(hashArr* h,char* ename)
{
    unsigned char* c=(unsigned char*)malloc(MD5_DIGEST_LENGTH*sizeof(unsigned char));
    char* actualpath=(char*)malloc((PATH_MAX+1)*sizeof(char));
    int flag;
    char* ptr;
    if((!c)||(!actualpath))
        exit(1);
    ptr=realpath(ename, actualpath);
    if(!ptr)
        exit(1);
    flag=md5Func(c,actualpath);
    if(!flag)            
        exit(1);   
    flag=insertHash(h,(void*)c,(void*)actualpath);
    if(flag==2)
    {
        printf("Duplicate File:%s.\n",actualpath);
    }
}

void findDupRec(hashArr* h,char *dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) 
    {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) 
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) 
        {
            /* Found a directory, but ignore . and .. */
            if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
                continue;
            /* Recurse at a new indent level */
            findDupRec(h,entry->d_name);
        }
        else 
        {
            checkDup(h,entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

int main()
{
    hashArr* h=NULL;
    char filename[PATH_MAX+1];/*="/home/sqrt11/Documents/";*/
    int flag=initFunc(&h,filename);
    if(!flag)
        exit(1);
    findDupRec(h,filename);
    forEachHash(h);
    destroyHash(h);
    return 0;
}