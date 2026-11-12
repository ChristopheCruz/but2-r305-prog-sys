/* R3.05 - Sujet 06 - Ex 10 : lamash, le mini-shell du LAMAE (squelette)
 * La lecture et le decoupage de la ligne sont fournis : a vous d'ecrire
 * l'execution des commandes (fork + execvp + waitpid) et les commandes
 * internes exit et status. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TAILLE_LIGNE 1024
#define MAX_MOTS 64

/* Decoupe ligne en mots (modifie ligne). mots[] est termine par NULL.
 * Renvoie le nombre de mots, ou -1 si la ligne contient trop de mots. */
static int decouper(char *ligne, char *mots[], int max)
{
    int n = 0;
    for (char *m = strtok(ligne, " \t\n"); m != NULL; m = strtok(NULL, " \t\n")) {
        if (n >= max - 1)            /* garder une place pour le NULL final */
            return -1;
        mots[n++] = m;
    }
    mots[n] = NULL;
    return n;
}

int main(void)
{
    char ligne[TAILLE_LIGNE];
    char *mots[MAX_MOTS];
    int dernierCode = 0;

    for (;;) {
        printf("lamash> ");
        fflush(stdout);
        if (fgets(ligne, sizeof ligne, stdin) == NULL) {   /* Ctrl+D */
            putchar('\n');
            break;
        }
        int n = decouper(ligne, mots, MAX_MOTS);
        if (n == -1) {
            fprintf(stderr, "lamash: trop d'arguments\n");
            continue;
        }
        if (n == 0)
            continue;

        /* TODO : commandes internes "exit" et "status" */

        /* TODO : fork ; dans le fils execvp(mots[0], mots), en cas d'echec
                  message sur stderr et exit(127) ; dans le pere waitpid
                  et mise a jour de dernierCode (WIFEXITED / WEXITSTATUS). */
        (void)dernierCode;
    }
    return EXIT_SUCCESS;
}
