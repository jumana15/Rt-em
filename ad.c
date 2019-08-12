#include<stdio.h>
#include<stdlib.h>
#include "ad.h"
int Binary_search_legal(meeting* a,int size,meeting* new)
{
    int i,j,med,low=0,high=size-1;
    float x=new->begin,y=new->end;
    while(low<=high)
    {
        med=(high-low)/2 + low;
        if((a[med].begin==x)||((x>a[med].begin)&&(x<a[med].end))||((y>a[med].begin)&&(y<=a[med].end)))
        {
            return -1;
        }
        if(a[med].begin>x)
        {
            high=med-1;
        }
        if(a[med].begin<x)
        {
            low=med+1;
        }
    }
    return low;
}
int Binary_search(meeting* a,int size,int x)
{
    int i,j,med,low=0,high=size-1;
    while(low<=high)
    {
        med=(high-low)/2 + low;
        if(a[med].begin==x)
        {
            return med;
        }
        if(a[med].begin>x)
        {
            high=med-1;
        }
        if(a[med].begin<x)
        {
            low=med+1;
        }
    }
    return -1;
}
meeting_l* createAD()
{
    meeting_l* list=(meeting_l*)malloc(sizeof(meeting_l));
    if(list)
    {
        list->meetingList=(meeting*)malloc(sizeof(meeting));
        list->size=1;
        list->index=0;
    }
    return list;
}
meeting* createMeeting(float begin,float end,int room)
{
    meeting *m;
    m=(meeting*)malloc(sizeof(meeting));
    if(!m)
        return NULL;
    m->begin=begin;
    m->end=end;
    m->room=room;
    return m;
}
meeting_l* sortMeeting(meeting_l* list,meeting* new)
{
    int i;
    int index=Binary_search_legal(list->meetingList,list->index,new);
    meeting *ip;
    if(index==-1)
        return NULL;
    if(list->index==list->size)
    {
        ip=(meeting*)realloc(list->meetingList,(list->size*2)*sizeof(meeting));
        if(!ip)
            return NULL;
        list->size*=2;
        list->meetingList=ip;
    }
    for(i=list->index; i>index; i--)
    {
        list->meetingList[i]=list->meetingList[i-1];
    }
    list->meetingList[index]=*new;
    list->index++;
    return list;
}
meeting_l* Mremove(meeting_l* list,float begin)
{
    meeting *ip;
    int i;
    int index=Binary_search(list->meetingList,list->index,begin);
    if(index!=-1)
    {
        ip=&list->meetingList[index];
        for(i=index; i<list->index-1; i++)
        {
            list->meetingList[index]=list->meetingList[index+1];
        }
        list->index--;
        free(ip);
        if((list->size>=2)&&(2*list->index<list->size))
        {
            list->meetingList=(meeting*)realloc(list->meetingList,(list->size/2)*sizeof(meeting));
            list->size/=2;
        }
    }
    return list;
}
meeting* find(meeting_l* list,float begin)
{
    int index=Binary_search(list->meetingList,list->index,begin);
    if(index==-1)
        return 	NULL;
    return &list->meetingList[index];
}
meeting_l* destroyAD(meeting_l* list)
{
    int i;
    if(list)
    {
        for(i=0; i<list->size; i++)
        {
            free(&list->meetingList[i]);
        }
        free(list);
    }
    return NULL;
}
void printAD(meeting_l* list)
{
    int i=0;
    printf("\nsize=%d\nindex=%d\n",list->size,list->index);
    for(i=0; i<list->index; i++)
        printf("%d: Start:%f End:%f Room Number:%d\n",i+1,list->meetingList[i].begin,list->meetingList[i].end,list->meetingList[i].room);
}
