#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 500000000

typedef struct {
    int first;
    int last;
    int id;
} MY_ARGS;

int* arr;
int results[2];

pthread_mutex_t lock;

void* myfunc(void * args) {
    MY_ARGS* my_args = (MY_ARGS*) args;
    int first = my_args->first;
    int last = my_args->last;
    int id = my_args->id;

    for (int i = first; i < last; i++) {
        results[id] = results[id] + arr[i];
    }

    return NULL;
}

int main() {
    arr = malloc(sizeof(int) * MAX_SIZE);
    for (int i = 0; i<MAX_SIZE; i++) {
        arr[i] = rand() % 5;
    }
    results[0] = 0;
    results[1] = 0;

    pthread_t th1;
    pthread_t th2;

    int mid = MAX_SIZE / 2;
    MY_ARGS args1 = {0, mid, 0};
    MY_ARGS args2 = {mid, MAX_SIZE, 1};

    pthread_create(&th1, NULL, myfunc, &args1);
    pthread_create(&th2, NULL, myfunc, &args2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s1 = %d \n", results[0]);
    printf("s2 = %d \n", results[1]);
    printf("results = %d \n", results[0] + results[1]);

    return 0;
}

// gcc -o th_005 -lpthread th_005.c
// time ./th_005
// https://www.bilibili.com/video/BV1kt411z7ND/?p=4&spm_id_from=pageDriver&vd_source=9102b8de9802df63ba2ffaa53c2d727e
