#define _POSIX_C_SOURCE 200809L   /* convention R3.05 : fonctions POSIX en -std=c17 */
/* drones_args.c -- exercice 2 (R3.05 Sujet 08) : version BOGUÉE à analyser
 * gcc -std=c17 -Wall -Wextra -pedantic -g -pthread drones_args.c -o drones_args
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_DRONES 5

static void *decoller(void *arg)
{
    int numero = *(int *) arg;      // on lit l'entier pointé... mais lequel ?
    printf("Drone %d : décollage !\n", numero);
    return NULL;
}

int main(void)
{
    pthread_t drones[NB_DRONES];

    for (int i = 0; i < NB_DRONES; i++)
        pthread_create(&drones[i], NULL, decoller, &i);   // <-- suspect
    for (int i = 0; i < NB_DRONES; i++)
        pthread_join(drones[i], NULL);
    return 0;
}
