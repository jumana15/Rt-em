#ifndef AD_H
#define AD_H
typedef struct
{
    float begin;
    float end;
    int room;
} meeting;
typedef struct
{
    int index;
    int size;
    meeting** meetingList;
} meeting_l;
int Binary_search_legal(meeting** a,int size,meeting* new);
int Binary_search(meeting** a,int size,int x);
meeting_l* createAD();
meeting* createMeeting(float begin,float end,int room);
meeting_l* sortMeeting(meeting_l* list,meeting* new);
meeting_l* Mremove(meeting_l* list,float begin);
meeting* find(meeting_l* list,float begin);
meeting_l* destroyAD(meeting_l* list);
void printAD(meeting_l* list);
#endif
