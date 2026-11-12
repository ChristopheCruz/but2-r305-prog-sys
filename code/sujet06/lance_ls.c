/* R3.05 - Sujet 06 - Ex 9 : changer de peau */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    printf("avant exec ");
    execlp("ls", "ls", "-l", (char *)NULL);   /* argv[0] = "ls", argv[1] = "-l" */
    perror("execlp");                         /* seulement si exec a echoue */
    return 1;
}
