#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 500000000

typedef struct {
    int first;
    int last;
    int result;
} MY_ARGS;

int* arr;

void* myfunc(void * args) {
    MY_ARGS* my_args = (MY_ARGS*) args;
    int first = my_args->first;
    int last = my_args->last;
    int s = 0;
    for (int i = first; i < last; i++) {
        s += arr[i];
    }
    my_args->result = s;

    return NULL;
}
pthread_mutex_t lock;

int main() {
    arr = malloc(sizeof(int) * MAX_SIZE);
    for (int i = 0; i<MAX_SIZE; i++) {
        arr[i] = rand() % 5;
    }

    pthread_t th1;
    pthread_t th2;

    int mid = MAX_SIZE / 2;
    MY_ARGS args1 = {0, mid, 0};
    MY_ARGS args2 = {mid, MAX_SIZE, 0};

    pthread_create(&th1, NULL, myfunc, &args1);
    pthread_create(&th2, NULL, myfunc, &args2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s1 = %d \n", args1.result);
    printf("s2 = %d \n", args2.result);
    printf("results = %d \n", args1.result + args2.result);

    return 0;
}

// gcc -o th_006 -lpthread th_006.c
// time ./th_006
// https://www.bilibili.com/video/BV1kt411z7ND/?p=4&spm_id_from=pageDriver&vd_source=9102b8de9802df63ba2ffaa53c2d727e
