/* R3.05 - Sujet 06 - Ex 2 : programme B (combien d'ouvrieres ?) */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    for (int i = 0; i < 3; i++) {
        if (fork() == 0)
            printf("ouvriere i=%d pid=%d ppid=%d\n", i, (int)getpid(), (int)getppid());
    }
    /* sleep(30); */
    return 0;
}
