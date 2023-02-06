#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    printf("hello, pid=%d\n", getpid());
    while(1) {
        printf("begin sleep...\n");
        sleep(1);
    }
}

//perf sched record -p {pid} --sleep 10
//perf sched script
