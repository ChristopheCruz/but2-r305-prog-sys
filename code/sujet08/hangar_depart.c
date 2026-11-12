/* hangar_depart.c -- point de départ de la mission 4 (R3.05 Sujet 08)
 * Un drone (un caractère) rebondit sur les murs du hangar.
 * gcc -std=c17 -Wall -Wextra -pedantic -g -pthread hangar_depart.c -o hangar
 */
#define _POSIX_C_SOURCE 200809L   // pour nanosleep avec -std=c17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "vt100.h"

#define LARGEUR 60     // colonnes 1..LARGEUR
#define HAUTEUR 20     // lignes 1..HAUTEUR
#define PAUSE_MS 50

typedef struct {
    int x, y;          // position (colonne, ligne), à partir de 1
    int dx, dy;        // vitesse : -1, 0 ou +1
    char symbole;
} Drone;

/* Mutex qui protège le terminal : une séquence GOTOYX + caractère
 * doit être écrite d'un seul bloc (section critique). */
static pthread_mutex_t ecran = PTHREAD_MUTEX_INITIALIZER;

static void pause_ms(long ms)
{
    struct timespec d = { ms / 1000, (ms % 1000) * 1000000L };
    nanosleep(&d, NULL);
}

static void dessiner(int x, int y, char c)
{
    /* TODO : protéger cet affichage avec le mutex ecran */
    printf(GOTOYX "%c", y, x, c);
    fflush(stdout);
}

static void dessinerMurs(void)
{
    for (int x = 1; x <= LARGEUR + 1; x++) { dessiner(x, 1, '#'); dessiner(x, HAUTEUR + 1, '#'); }
    for (int y = 1; y <= HAUTEUR + 1; y++) { dessiner(1, y, '#'); dessiner(LARGEUR + 1, y, '#'); }
}

static void *voler(void *arg)
{
    Drone *d = arg;
    (void) d;
    /* TODO : boucle de déplacement
     *   - effacer l'ancienne position (espace)
     *   - rebondir si la prochaine position touche un mur
     *   - avancer, dessiner, faire une pause
     * Pour l'exercice, borner le nombre de pas (ex. 400) plutôt qu'une boucle infinie.
     */
    return NULL;
}

int main(void)
{
    Drone d = { 10, 5, 1, 1, 'o' };
    pthread_t t;

    printf(CLEARSCR CURSOFF);
    dessinerMurs();

    int rc = pthread_create(&t, NULL, voler, &d);
    if (rc != 0) {
        fprintf(stderr, "pthread_create : %s\n", strerror(rc));
        return EXIT_FAILURE;
    }
    pthread_join(t, NULL);

    printf(GOTOYX CURSON NORMAL "\n", HAUTEUR + 3, 1);
    (void) pause_ms;   // à supprimer quand vous l'utiliserez
    (void) &ecran;     // idem
    return EXIT_SUCCESS;
}
