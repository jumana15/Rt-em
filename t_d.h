#ifndef T_D_H
#define T_D_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct
{
    unsigned int hour;
    unsigned int min;
    unsigned int sec;
}cTime_t;

typedef struct
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
    unsigned int DayOfYear;
    unsigned int IsLeap;
}cDate_t;

typedef cTime_t* CT;

typedef cDate_t* CD;

const char* Mon[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
const char* MonNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
const int days_sum[12]={0,31,59,90,120,151,181,212,243,273,304,334};
const int days_num[12]={31,29,31,30,31,30,31,31,30,31,30,31};

int setTime(CT* t, int h, int m,  int s);
void printTime(cTime_t* t);
int getTime(cTime_t *t,unsigned int *h,unsigned int *m, unsigned int *s);
int addTime(cTime_t* t1,cTime_t* t2);
int setDate(CD *date,unsigned int d,unsigned int m, unsigned int y);
void printDate(cDate_t* d);
int getDate(cDate_t* date,unsigned int* d,unsigned int* m,unsigned int* y,unsigned int* dy, unsigned int* l,const char* s);
#endif
