/* R3.05 - Sujet 06 - Ex 2 : programme A (combien de bzz ?) */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    fork();
    fork();
    fork();
    printf("bzz %d\n", (int)getpid());
    return 0;
}
