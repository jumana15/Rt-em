#ifndef FILES_H
#define FILES_H

typedef struct
{
    char* str;
    int count;
} wordOccurrences;

typedef struct
{
    int size;
    int index;
    wordOccurrences**  wCount;
} stock;

void PrintLastN(FILE* ptr,FILE* output,int N);
void char_counter(FILE* ptr,FILE* output);
stock* init_S(stock* s,int size);
int insert(stock* s,char* str);
int word_counter(FILE* input,FILE* output,int size);
#endif
