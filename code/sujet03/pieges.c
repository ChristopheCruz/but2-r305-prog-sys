/* R3.05 - Sujet 03 - Mission 3 : le labyrinthe piégé
 * Ce programme CONTIENT VOLONTAIREMENT 4 erreurs mémoire.
 * Il compile sans avertissement : c'est bien là le danger !
 * Compilez-le ensuite avec : -fsanitize=address,undefined -g
 */
#include <stdio.h>
#include <stdlib.h>

#define N 5

/* Piège A : renvoie l'adresse d'une variable locale */
int *creerCompteur(int depart)
{
    int compteur = depart;
    int *adresse = &compteur;
    return adresse;
}

/* Piège B : cherche une valeur, renvoie NULL si absente */
int *chercher(int *tab, int n, int valeur)
{
    for (int k = 0; k < n; k++)
        if (tab[k] == valeur)
            return &tab[k];
    return NULL;
}

int main(int argc, char *argv[])
{
    int tab[N] = {4, 8, 15, 16, 23};
    int *q = NULL;

    /* Piège C : on parcourt un élément de trop */
    int somme = 0;
    for (int *p = tab; p <= tab + N; p++)
        somme += *p;
    printf("somme = %d\n", somme);

    /* Piège B (suite) : 42 n'est pas dans le tableau */
    int *trouve = chercher(tab, N, 42);
    printf("trouvé : %d\n", *trouve);

    int *cpt = creerCompteur(10);
    printf("compteur = %d\n", *cpt);

    /* Piège D : q n'est initialisé que si on passe un argument */
    if (argc > 1)
        q = &tab[atoi(argv[1])];
    *q = 0;
    printf("tab[0] = %d\n", tab[0]);
    return 0;
}
