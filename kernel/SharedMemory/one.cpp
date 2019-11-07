#include <unistd.h>
#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std; 
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("share.txt",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
   int* pointer= (int*) shmat(shmid,(void*)0,0); 
  
    //printf("Data read from memory: %d\n",*pointer); 
    
    while(1) 
    { 
        printf("the value is %d\n", *pointer); 
        sleep(1); 
    }  
    //detach from shared memory  
    shmdt(pointer); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 
