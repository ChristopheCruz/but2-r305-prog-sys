#define _POSIX_C_SOURCE 200809L   /* convention R3.05 : fonctions POSIX en -std=c17 */
/* compteur.c -- point de départ des exercices 3 et 4 (R3.05 Sujet 08)
 * Deux threads incrémentent N fois la même variable globale, SANS protection.
 * gcc -std=c17 -Wall -Wextra -pedantic -g -pthread compteur.c -o compteur
 * ./compteur 1000000
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static long compteur = 0;   // donnée partagée
static long n = 1000000;    // nombre d'incréments par thread

static void *incrementer(void *arg)
{
    (void) arg;                     // paramètre inutilisé
    for (long i = 0; i < n; i++)
        compteur++;                 // section critique NON protégée
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        char *fin;
        n = strtol(argv[1], &fin, 10);
        if (*fin != '\0' || n <= 0) {
            fprintf(stderr, "usage : %s [nombre_d_increments > 0]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    pthread_t t1, t2;
    int rc;
    if ((rc = pthread_create(&t1, NULL, incrementer, NULL)) != 0) {
        fprintf(stderr, "pthread_create : %s\n", strerror(rc));
        return EXIT_FAILURE;
    }
    if ((rc = pthread_create(&t2, NULL, incrementer, NULL)) != 0) {
        fprintf(stderr, "pthread_create : %s\n", strerror(rc));
        return EXIT_FAILURE;
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("attendu : %ld   obtenu : %ld   perdus : %ld\n",
           2 * n, compteur, 2 * n - compteur);
    return EXIT_SUCCESS;
}
