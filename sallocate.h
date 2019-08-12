#ifndef SALLOCATE_H
#define SALLOCATE_H
typedef int* intPtr;
typedef struct
{
    int** arr;
    int index;
    int size;
}DA_t;
DA_t* createDA(int size);
int insert(DA_t* s,intPtr num);
void printDA(DA_t* s);
void destroyDA(DA_t* s);
#endif
