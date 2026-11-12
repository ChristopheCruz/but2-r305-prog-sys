/* R3.05 - Sujet 03 - Mission 4 : la calculatrice du LAMAE (fichier de départ)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g calculatrice_depart.c -o calc
 */
#include <stdio.h>
#include <stdlib.h>

typedef int (*Operation)(int, int);   /* type « pointeur vers fonction (int,int) -> int » */

int addition(int a, int b)       { return a + b; }
int soustraction(int a, int b)   { return a - b; }
int multiplication(int a, int b) { return a * b; }
int division(int a, int b)
{
    /* TODO : refuser la division par zéro ET le cas INT_MIN / -1 */
    return a / b;
}

int main(void)
{
    Operation operations[] = {addition, soustraction, multiplication, division};
    const char *symboles[] = {"+", "-", "*", "/"};
    const int nbOperations = (int)(sizeof operations / sizeof operations[0]);

    (void)symboles;        /* à supprimer quand vous utiliserez symboles */
    (void)nbOperations;    /* idem */

    /* TODO (Ex 9)  : boucle qui teste les 4 opérations sur 5 et 3
     * TODO (Ex 10) : menu interactif ; VALIDER le choix AVANT d'appeler operations[choix] */
    return EXIT_SUCCESS;
}
