#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct Test
{
    int num;
    int age;
};

// struct Test t;

void* callback(void* arg)
{
    for (int i = 0; i< 5; i++) 
    {
        printf("child thread: i = %d\n", i);
    }
    printf("child thread: %ld\n", pthread_self());

    struct Test* t = (struct Test*)arg;
    t->age = 6;
    t->num = 100;
    pthread_exit(t);

    return NULL;
}

int main() 
{
    struct Test t;
    pthread_t tid;
    pthread_create(&tid, NULL, callback, &t);
    printf("main thread: %ld\n", pthread_self());

    pthread_detach(tid);

    pthread_exit(NULL);

    return 0;
}

// gcc pthread_detach.c -lpthread -o detach
