#define _POSIX_C_SOURCE 200809L   /* convention R3.05 : fonctions POSIX en -std=c17 */
/* virement.c -- exercice 5 (R3.05 Sujet 08) : deux drones échangent de l'énergie.
 * Ce programme peut se BLOQUER définitivement (Ctrl+C pour l'arrêter).
 * gcc -std=c17 -Wall -Wextra -pedantic -g -pthread virement.c -o virement
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    long energie;
    pthread_mutex_t verrou;
} Batterie;

static Batterie a = { 1, 1000, PTHREAD_MUTEX_INITIALIZER };
static Batterie b = { 2, 1000, PTHREAD_MUTEX_INITIALIZER };

static void transferer(Batterie *src, Batterie *dst, long quantite)
{
    pthread_mutex_lock(&src->verrou);
    pthread_mutex_lock(&dst->verrou);
    src->energie -= quantite;
    dst->energie += quantite;
    pthread_mutex_unlock(&dst->verrou);
    pthread_mutex_unlock(&src->verrou);
}

static void *drone_a_vers_b(void *arg)
{
    (void) arg;
    for (int i = 0; i < 100000; i++)
        transferer(&a, &b, 1);
    return NULL;
}

static void *drone_b_vers_a(void *arg)
{
    (void) arg;
    for (int i = 0; i < 100000; i++)
        transferer(&b, &a, 1);
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, drone_a_vers_b, NULL);
    pthread_create(&t2, NULL, drone_b_vers_a, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("A = %ld, B = %ld, total = %ld (attendu 2000)\n",
           a.energie, b.energie, a.energie + b.energie);
    return 0;
}
