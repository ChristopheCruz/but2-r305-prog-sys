/* R3.05 - Sujet 04 - fantomes.c
 * Programme VOLONTAIREMENT bogue : 4 "fantomes" de la memoire se cachent ici.
 * Mission : les trouver avec -fsanitize=address et/ou valgrind, puis les corriger.
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g fantomes.c -o fantomes
 * Chasse     : gcc -std=c17 -Wall -Wextra -pedantic -g -fsanitize=address fantomes.c -o fantomes_asan
 * Usage      : ./fantomes_asan 1   (puis 2, 3, 4 : un fantome par numero)
 * Remarque   : gcc >= 12 signale deja deux fantomes a la compilation (-Wuse-after-free) :
 *              ces avertissements sont VOULUS ici. Lisez-les !
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fantome 1 : quelque chose ne revient jamais au tas... */
static void fantome1(void)
{
    for (int i = 0; i < 3; i++) {
        int *t = malloc(100 * sizeof *t);
        if (t == NULL)
            return;
        t[0] = i;
        printf("bloc %d alloue en %p\n", t[0], (void *)t);
    }
}

/* Fantome 2 : on lit une maison deja demolie */
static void fantome2(void)
{
    char *nom = malloc(16);
    if (nom == NULL)
        return;
    strcpy(nom, "LAMAE");
    free(nom);
    printf("nom = %s\n", nom);
}

/* Fantome 3 : on demolit deux fois la meme maison */
static void fantome3(void)
{
    int *p = malloc(sizeof *p);
    if (p == NULL)
        return;
    *p = 42;
    int *q = p;
    free(p);
    free(q);
}

/* Fantome 4 : une case de trop */
static void fantome4(void)
{
    size_t n = 10;
    int *t = malloc(n * sizeof *t);
    if (t == NULL)
        return;
    for (size_t i = 0; i <= n; i++)
        t[i] = (int)i;
    printf("dernier = %d\n", t[n - 1]);
    free(t);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage : %s numero_du_fantome (1 a 4)\n", argv[0]);
        return EXIT_FAILURE;
    }
    switch (atoi(argv[1])) {
    case 1: fantome1(); break;
    case 2: fantome2(); break;
    case 3: fantome3(); break;
    case 4: fantome4(); break;
    default: fprintf(stderr, "numero inconnu\n"); return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
