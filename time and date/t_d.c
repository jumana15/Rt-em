#include "t_d.h"

int setTime(CT* t, int h, int m,  int s)
{
    if(!t[0])
    {
        t[0]=(cTime_t*)malloc(sizeof(cTime_t));
    }
    if((t[0])&&(h>=0)&&(h<24)&&(m>=0)&&(m<60)&&(s>=0)&&(s<60))
    {
        t[0]->hour=h;
        t[0]->min=m;
        t[0]->sec=s;
        return 1;
    }
    else
        if(t[0])
            free(t[0]);
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

int setDate(CD *date,unsigned int d,unsigned int m, unsigned int y)
{
    int days_sum[12]={0,31,59,90,120,151,181,212,243,273,304,334};
    int days_num[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(!date[0])
    {
        date[0]=(cDate_t*)malloc(sizeof(cDate_t));
    }
    if((date[0])&&(d>=0)&&(d<=days_num[m-1])&&(m>=0)&&(m<=12)&&(y>=0))
    {
        date[0]->year=y;
        date[0]->IsLeap=(!(y%4));
        if((m==2)&&((!(date[0]->IsLeap))&&(m>28)))
        {
            free(date[0]);
            return 0;
        }
        date[0]->day=d;
        date[0]->month=m;
        date[0]->DayOfYear=days_sum[m-1]+d;
	if(m>2)
		date[0]->DayOfYear+=date[0]->IsLeap;
        return 1;
    }
    else
        if(date[0])
            free(date[0]);
    return 0;
}

void printDate(cDate_t* d)
{
    char* Mon[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char sd[3]="00",sm[3]="00";
    if(!d)
    {
        printf("There's no Date to print!\n");
        return;
    }
    sd[0]=d->day/10+'0';
    sd[1]=d->day%10+'0';
    sm[0]=d->month/10+'0';
    sm[1]=d->month%10+'0';
    printf("%s/%s/%u\n",sd,Mon[d->month-1],d->year);
    printf("%s/%s/%u    European\n",sd,sm,d->year);
    printf("%s/%s/%u    American\n",sm,sd,d->year);
}

int getDate(cDate_t* date,unsigned int* d,unsigned int* m,unsigned int* y,unsigned int* dy, unsigned int* l,const char* s)
{
    char* MonNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
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


