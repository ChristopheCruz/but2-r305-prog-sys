/* R3.05 - Sujet 06 - Ex 3 : le message fantome */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    printf("la reine s'eveille... ");   /* pas de \n ! */
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
    printf("[%s]\n", pid == 0 ? "fils" : "pere");
    if (pid > 0)
        waitpid(pid, NULL, 0);
    return EXIT_SUCCESS;
}
