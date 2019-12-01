#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
struct data_for_thread {
    volatile long counter;
    // pad to 64 bytes
    // long = 8 bytes
    // this means we need 64-8 = 56 bytes padding
    char nothing[56];
};
void* thr(void* data) {
    struct data_for_thread* d=(struct data_for_thread*)data;
    while(1) {
        d->counter++;
    }
    return NULL;
}
void check_zero(int ret) {
    if(ret!=0) {
        fprintf(stderr, "failed!\n");
        exit(1);
    }
}
int main(int argc, char** argv, char** envp) {
    struct data_for_thread* data_one;
    struct data_for_thread* data_two;
    int ret;
    ret=posix_memalign((void**)&data_one, 64, sizeof(struct data_for_thread));
    check_zero(ret);
    ret=posix_memalign((void**)&data_two, 64, sizeof(struct data_for_thread));
    check_zero(ret);
    data_one->counter=0;
    data_two->counter=0;
    pthread_t thr1_pt, thr2_pt;
    printf("address of counter1 is %ln\n", &data_one->counter);
    printf("address of counter2 is %ln\n", &data_two->counter);
    pthread_create(&thr1_pt, NULL, thr, data_one);
    pthread_create(&thr2_pt, NULL, thr, data_two);
    long tmp_x=data_one->counter;
    long tmp_y=data_two->counter;
    while(1) {
        sleep(1);
        long new_tmp_x=data_one->counter;
        long new_tmp_y=data_two->counter;
        long work=(new_tmp_x-tmp_x)+(new_tmp_y-tmp_y);
        printf("work is %ld\n", work);
        tmp_x=new_tmp_x;
        tmp_y=new_tmp_y;
    }
    return 0;
}
