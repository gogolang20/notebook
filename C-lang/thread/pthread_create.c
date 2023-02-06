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

    // for(int i=0; i<5; ++i)
    // {
    //     printf("main thread: i = %d\n", i);
    // }

    printf("main thread: %ld\n", pthread_self());
    // pthread_exit(NULL); // 线程退出函数 子线程仍然会执行

    void* ptr;
    pthread_join(tid, &ptr); // 线程回收
    // struct Test* pt = (struct Test*)ptr;
    printf("num: %d, age: %d\n", t.num, t.age);

    return 0;
}

// gcc pthread_create.c -lpthread -o create
