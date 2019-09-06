#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include "md5m.h"
int md5Func(unsigned char* c,char* filename)
{
    FILE *inFile = fopen (filename, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[128];
    if (!inFile) 
    {
        printf ("%s can't be opened.\n", filename);
        return 0;
    }
    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 128, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);
    fclose (inFile);
    return 1;
}