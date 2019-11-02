#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>  
#include <pwd.h>
#include <grp.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

int maxSize;

bool compareFunction(char* a,char* b)
{
    return strcasecmp(a,b)<0;
}

static void filetype(mode_t m, char* p) 
{
    if(S_ISREG(m)) 
    {
        p[0]='-';
    }
    if(S_ISDIR(m)) 
    {
        p[0]='d';
    }
    if(S_ISCHR(m))
    {
        p[0]='c';
    }
    if(S_ISBLK(m)) 
    {
        p[0]='b';
    }
    if(S_ISFIFO(m)) 
    {
        p[0]='p';
    }
    if(S_ISLNK(m)) 
    {
        p[0]='l';
    }
    if(S_ISSOCK(m)) 
    {
        p[0]='s';
    }
    for(int i=1; i<10; i++) 
    {
        p[i]='-';
    }
    if(S_IRUSR & m) 
    {
        p[1]='r';
    }
    if(S_IWUSR & m) 
    {
        p[2]='w';
    }
    if(S_IXUSR & m) 
    {
        p[3]='x';
    }
    if(S_IRGRP & m) 
    {
        p[4]='r';
    }
    if(S_IWGRP & m) 
    {
        p[5]='w';
    }
    if(S_IXGRP & m)
    {
        p[6]='x';
    }
    if(S_IROTH & m) 
    {
        p[7]='r';
    }
    if(S_IWOTH & m) 
    {
        p[8]='w';
    }
    if(S_IXOTH & m) 
    {
        p[9]='x';
    }
    p[10]='\0';
}

void printVec(vector<char*> &v,size_t total,char* name)
{
    DIR *dp=opendir(name);
    chdir(name);
    struct stat statbuf;
    struct passwd *pwd;
    struct group *grp;
    time_t now;
    char p[11];
    char str[32],spaces[256];
    int i;
    sort(v.begin(),v.end(),compareFunction);
    cout<<"total "<<total<<endl;
    for(vector<char*>::iterator it=v.begin();it!=v.end();it++)
    {
        lstat(*it,&statbuf);
        filetype(statbuf.st_mode,p);
        pwd = getpwuid(statbuf.st_uid);
        grp = getgrgid(statbuf.st_gid);
        if((!pwd)||(!grp)) 
        {
           throw string("Error!");
        } 
        time(&now);
        if(difftime(now,statbuf.st_atime)>=(3*30+3*31)*24*60*60)
        {
            strftime(str, sizeof(str), "%b %d %Y", localtime(&statbuf.st_mtime));
        }
        else
        {
            strftime(str, sizeof(str), "%b %d %H:%M", localtime(&statbuf.st_mtime));
        }
        for(i=0;i<maxSize-ceil(log10(statbuf.st_size));i++)
        {
            spaces[i]=' ';
        }
        spaces[i]='\0';
        cout<<p<<" "<<statbuf.st_nlink<<" "<<pwd->pw_name<<" "<<grp->gr_name<<" "<<spaces<<statbuf.st_size<<" "<<str<<" "<<*it<<endl;
    }
    closedir(dp);
}

size_t filesScan(char* name,vector<char*> &v)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    size_t total=0;
    int len;
    if((dp = opendir(name)) == NULL) 
    {
        throw string("cannot open directory!");
    }
    chdir(name);
    while((entry = readdir(dp)) != NULL) 
    {
        lstat(entry->d_name,&statbuf);
        if((!strcmp(".",entry->d_name))||(!strcmp("..",entry->d_name)))
                continue;
        total+=statbuf.st_blocks;
        len=ceil(log10(statbuf.st_size));
        maxSize=maxSize<len?len:maxSize;
        v.push_back(entry->d_name);
   	}
    sort(v.begin(),v.end(),compareFunction);
    chdir("..");
    closedir(dp);
    return total;
}

int main()
{
    vector<char*>v;
    char name[]="/home/sqrt11/Documents/sp/";
    size_t total=0;
    maxSize=0;
    try
    {
        total=filesScan(name,v);
    }
    catch(string s)
    {
        cout<<s<<endl;
        return 0;
    }
    try
    {
        printVec(v,total/2,name);
    }
    catch(string s)
    {
        cout<<s<<endl;
        return 0;
    }
    return 0;
}