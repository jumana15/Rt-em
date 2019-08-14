#include "t_d.h"
int main()
{
    CT *t= (CT*)malloc(sizeof(CT));
    CD *d= (CD*)malloc(sizeof(CD));
    time_t time_date;
    struct tm* current_time;
    time_date = time(0);/* current time in seconds*/
    current_time = localtime(&time_date);
    printf("%d %d %d %d %d %d\n",current_time->tm_hour,current_time->tm_min,current_time->tm_sec,current_time->tm_mon + 1,current_time->tm_mday,current_time->tm_year + 1900);
    setTime(t,current_time->tm_hour,current_time->tm_min,current_time->tm_sec);
    printTime(t[0]);
    setDate(d,current_time->tm_mday,current_time->tm_mon + 1,current_time->tm_year + 1900);
    printDate(d[0]);


    return 0;
}
