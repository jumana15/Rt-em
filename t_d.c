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
const char* Mon[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
const char* MonNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
const int days_sum[12]={0,31,59,90,120,151,181,212,243,273,304,334};
const int days_num[12]={31,29,31,30,31,30,31,31,30,31,30,31};

int setTime(cTime_t* t,unsigned int h,unsigned int m, unsigned int s)
{
    if(!t)
    {
        t=(cTime_t*)malloc(sizeof(cTime_t));
    }
    if((t)&&(h>=0)&&(h<24)&&(m>=0)&&(m<60)&&(s>=0)&&(s<60))
    {
        t->hour=h;
        t->min=m;
        t->sec=s;
        return 1;
    }
    else
        if(t)
            free(t);
    return 0;
}

void printTime(cTime_t* t)
{
    if(!t)
    {
        printf("There's no time to print!\n");
        return;
    }
    printf("%u:%u:%u\n",t->hour,t->min,t->sec);
    if(t->hour<=12)
        printf("%u:%u:%u AM\n",t->hour%12,t->min,t->sec);
    else
        printf("%u:%u:%u PM\n",t->hour%12,t->min,t->sec);
}

int getTime(cTime_t *t,unsigned int *h,unsigned int *m, unsigned int *s)
{
    if(!t)
        return 0;
    h=&t->hour;
    m=&t->min;
    s=&t->sec;
    return 1;
}

int addTime(cTime_t* t1,cTime_t* t2)
{
    int flag1=0,flag2=0;
    if((!t1)||(!t2))
    {
        printf("Objects can't be added!\n");
        return 0;
    }
    t1->sec+=t2->sec;
    if(t1->sec>=60)
    {
        flag1=1;
        t1->sec%=60;
    }
    t1->min=t1->min+t2->min+flag1;
    if(t1->min>=60)
    {
        flag2=1;
        t1->min%=60;
    }
    t1->hour=t1->hour+t2->hour+flag2;
    if(t1->hour>=24)
        t1->hour%=24;
}

int setDate(cDate_t* date,unsigned int d,unsigned int m, unsigned int y)
{
    if(!date)
    {
        date=(cDate_t*)malloc(sizeof(cDate_t));
    }
    if((date)&&(d>=0)&&(d<=days_num[m-1])&&(m>=0)&&(m<=12)&&(y>=0))
    {
        date->year=y;
        date->IsLeap=y%4;
        if((m==2)&&((!(date->IsLeap))&&(m>28)))
        {
            free(date);
            return 0;
        }
        date->day=d;
        date->month=m;
        date->DayOfYear=days_sum[m-1]+d+(!date->IsLeap);
        return 1;
    }
    else
        if(date)
            free(date);
    return 0;
}

void printDate(cDate_t* d)
{
    char sd[3]="00",sm[3]="00";
    if(!d)
    {
        printf("There's no Date to print!\n");
        return;
    }
    sd[0]=d->day/10;
    sd[1]=d->day%10;
    sm[0]=d->month/10;
    sm[1]=d->month%10;
    printf("%s/%s/%u\n",sd,Mon[d->month-1],d->year);
    printf("%s/%s/%u    European\n",sd,sm,d->year);
    printf("%s/%s/%u    American\n",sm,sd,d->year);
}

int getDate(cDate_t* date,unsigned int* d,unsigned int* m,unsigned int* y,unsigned int* dy, unsigned int* l,const char* s)
{
    if(!date)
        return 0;
    d=&date->day;
    m=&date->month;
    y=&date->year;
    dy=&date->DayOfYear;
    l=&date->IsLeap;
    s=MonNames[date->month-1];
    return 1;
}

int main()
{
    cTime_t *t;
    cDate_t *d;
    time_t time_date;
    struct tm* current_time;
    time_date = time(0);/* current time in seconds*/
    current_time = localtime(&time_date);
    printf("%d %d %d %d %d %d\n",current_time->tm_hour,current_time->tm_min,current_time->tm_sec,current_time->tm_mon + 1,current_time->tm_mday,current_time->tm_year + 1900);
    setTime(t,current_time->tm_hour,current_time->tm_min,current_time->tm_sec);
    printTime(t);
    setDate(d,current_time->tm_mday,current_time->tm_mon + 1,current_time->tm_year + 1900);
    printDate(d);


    return 0;
}
