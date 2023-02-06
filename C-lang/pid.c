#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int x = 1;

    pid_t pid = fork();
    if (pid == 0) {
        printf("child = %d\n", ++x);
        exit(0);
    }

    printf("parent = %d\n", --x);
    exit(0);
}

// gcc -o pid pid.c
