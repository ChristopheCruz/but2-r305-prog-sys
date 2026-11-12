/* R3.05 - Sujet 06 - Ex 7 : la reine et ses N ouvrieres (squelette) */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 5

/* Travail d'une ouvriere : ne revient jamais (se termine par exit). */
static void travailler(int i)
{
    /* TODO : srand(getpid()); dormir rand() % 4 secondes,
       afficher "ouvriere i (PID) : recolte terminee", puis exit(i * 10). */
    (void)i;
    exit(EXIT_SUCCESS);
}

int main(void)
{
    pid_t ouvrieres[N];

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            /* TODO : que faire des ouvrieres deja creees ? */
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
            travailler(i);          /* le fils ne revient JAMAIS dans la boucle */
        ouvrieres[i] = pid;
    }

    /* TODO 1 : recueillir les N ouvrieres avec wait() et afficher PID + code. */
    /* TODO 2 : variante avec waitpid(ouvrieres[i], &statut, 0).               */
    (void)ouvrieres;
    return EXIT_SUCCESS;
}
