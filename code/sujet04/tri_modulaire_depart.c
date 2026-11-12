/* R3.05 - Sujet 04 - Banc d'essai des tris : fichier de depart
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g tri_modulaire_depart.c -o tri
 * Les fonctions marquees A_FAIRE sont a completer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    long comparaisons;
    long echanges;
    double temps_ms;
} Statistiques;

/* Type "algorithme de tri" : pointeur de fonction (cf. sujet 03) */
typedef void (*AlgoTri)(int *tab, size_t n, Statistiques *stats);

/* ---------- Algorithmes ---------- */
void triBulle(int *tab, size_t n, Statistiques *stats)
{
    stats->comparaisons = 0;
    stats->echanges = 0;
    /* A_FAIRE (Ex 7) : incrementer stats->comparaisons et stats->echanges */
    (void)tab; (void)n;
}

void triSelection(int *tab, size_t n, Statistiques *stats)
{
    stats->comparaisons = 0;
    stats->echanges = 0;
    /* A_FAIRE (Ex 8) */
    (void)tab; (void)n;
}

void triInsertion(int *tab, size_t n, Statistiques *stats)
{
    stats->comparaisons = 0;
    stats->echanges = 0;
    /* A_FAIRE (Ex 8) : compter un "echange" par decalage */
    (void)tab; (void)n;
}

/* ---------- Utilitaires (Ex 9) ---------- */
void afficherTableau(const int *tab, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", tab[i]);
    printf("\n");
}

/* Renvoie une COPIE allouee dynamiquement (a liberer par l'appelant), NULL si echec */
int *dupliquerTableau(const int *source, size_t n)
{
    /* A_FAIRE */
    (void)source; (void)n;
    return NULL;
}

/* Renvoie 1 si le tableau est trie par ordre croissant, 0 sinon */
int estTrie(const int *tab, size_t n)
{
    /* A_FAIRE */
    (void)tab; (void)n;
    return 0;
}

/* Alloue et remplit un tableau de n entiers dans [0, max[, NULL si echec */
int *genererAleatoire(size_t n, int max)
{
    /* A_FAIRE */
    (void)n; (void)max;
    return NULL;
}

void afficherStats(Statistiques s)
{
    printf("comparaisons : %ld, echanges : %ld, temps : %.3f ms\n",
           s.comparaisons, s.echanges, s.temps_ms);
}

int main(void)
{
    AlgoTri algorithmes[] = { triBulle, triSelection, triInsertion };
    const char *noms[] = { "Tri a bulles", "Tri par selection", "Tri par insertion" };
    const size_t nbAlgos = sizeof algorithmes / sizeof algorithmes[0];

    int initial[] = { 64, 34, 25, 12, 22, 11, 90 };
    size_t n = sizeof initial / sizeof initial[0];

    /* A_FAIRE (Ex 10) : menu, copie dynamique, comparaison, liberation */
    for (size_t i = 0; i < nbAlgos; i++)
        printf("%zu. %s\n", i + 1, noms[i]);
    afficherTableau(initial, n);
    return EXIT_SUCCESS;
}
