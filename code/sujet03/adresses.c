/* R3.05 - Sujet 03 - Mission 0 : cartographier la mémoire
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g adresses.c -o adresses
 */
#include <stdio.h>

#define N 5

int globale = 42;             /* variable globale (segment de données) */

int main(void)
{
    int i = 3, j = 6;
    double x = 3.14;
    char c = 'Z';
    int tab[N] = {1, 2, 6, 0, 7};
    int *p = &i;

    /* %p attend un void * : on convertit explicitement */
    printf("objet      adresse              valeur\n");
    printf("i          %p   %d\n", (void *)&i, i);
    printf("j          %p   %d\n", (void *)&j, j);
    printf("x          %p   %f\n", (void *)&x, x);
    printf("c          %p   %c\n", (void *)&c, c);
    printf("p          %p   %p\n", (void *)&p, (void *)p);
    printf("globale    %p   %d\n", (void *)&globale, globale);
    for (int k = 0; k < N; k++)
        printf("tab[%d]     %p   %d\n", k, (void *)&tab[k], tab[k]);

    /* TODO (Ex 1) : afficher sizeof de chaque objet avec %zu */
    return 0;
}
