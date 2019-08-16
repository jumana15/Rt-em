#ifndef BITMAP_H
#define BITMAP_H

typedef struct
{
	int N;
	int* arr;
}bitmap;

typedef int (*func)(bitmap*,int);

void Int2Bin(int num,char* str);
int bitOn(bitmap* b,int bit);
int bitOff(bitmap* b,int bit);
int bitStatus (bitmap* b,int bit);
bitmap* create(int N);
void destroy(bitmap* b);

#endif
