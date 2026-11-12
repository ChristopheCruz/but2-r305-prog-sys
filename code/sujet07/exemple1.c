/* Sujet 07 - Exemple 1 (version corrigée) : communication PERE --> FILS par tube.
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g exemple1.c -o exemple1
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <string.h>     /* strlen */
#include <unistd.h>     /* pipe, fork, read, write, close */
#include <sys/types.h>
#include <sys/wait.h>   /* wait */

static const char message[] = "Cela provient d'un tube";   /* 23 caractères + '\0' */

int main(void)
{
    int p[2];

    if (pipe(p) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {                 /* fils : lecteur */
        char c;
        close(p[1]);                /* indispensable : sinon read ne renverra jamais 0 */
        while (read(p[0], &c, 1) > 0)
            putchar(c);
        putchar('\n');
        close(p[0]);
        exit(EXIT_SUCCESS);
    }

    /* père : écrivain */
    close(p[0]);
    if (write(p[1], message, strlen(message)) == -1)
        perror("write");
    close(p[1]);                    /* le fils verra la fin de fichier */
    wait(NULL);                     /* on n'abandonne pas son fils */
    return EXIT_SUCCESS;
}
