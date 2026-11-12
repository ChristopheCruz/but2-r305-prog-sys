/* R3.05 - Sujet 01 - Exercice 7 : ouvrir le coffre (squelette)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g devine.c -o devine
 */
#include <stdio.h>
#include <stdlib.h>   /* srand, rand */
#include <time.h>     /* time */

#define MAX_ESSAIS 10

/* Vide la fin de la ligne courante sur stdin (après une saisie invalide). */
static void viderLigne(void)
{
    int c;                                   /* int, pas char : EOF ! */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void)
{
    srand((unsigned) time(NULL));
    int valeurATrouver = rand() % 100;

    /* TODO : boucle de jeu (au plus MAX_ESSAIS essais)
     *   - lire une proposition avec scanf en TESTANT sa valeur de retour
     *   - en cas de saisie invalide : message sur stderr + viderLigne()
     *   - répondre « trop grand », « trop petit » ou « coffre ouvert ! »
     */
    (void) valeurATrouver;
    viderLigne();
    return 0;
}
