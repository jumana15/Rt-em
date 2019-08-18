#ifndef PACK_H
#define PACK_H

typedef struct 
{
		 unsigned int a	:4;
		 unsigned int b :4;
}ch;
union letters
{
	unsigned char c;
	ch d;
};

int compress1(unsigned char* s);

int compress2(unsigned char* s)
;
#endif
