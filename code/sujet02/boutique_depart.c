/* R3.05 - Sujet 02 - Mission 6 : fichier de départ de la boutique.
 * Complétez les définitions de types (ex. 6.1) puis les fonctions (ex. 6.2, 6.3).
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g boutique_depart.c -o boutique */
#include <stdio.h>
#include <string.h>

#define NB_OBJETS 8
#define TAILLE_NOM 40
#define TAILLE_REF 8

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char nom[TAILLE_NOM];
    char ref[TAILLE_REF];
    Date sortie;
    double prix;
    int stock;
} Objet;

/* Données de la boutique (prix et stocks fictifs). */
static Objet catalogue[NB_OBJETS] = {
    {"Faucon Millenium",                "SW-41", {1, 3, 2021}, 129.90, 3},
    {"Tie Advanced X1 Prototype",       "SW-31", {1, 1, 2021},  34.90, 12},
    {"X-Wing Black One",                "SW-30", {1, 1, 2021},  39.90, 9},
    {"Imperial Star Destroyer",         "SW-34", {1, 2, 2021},  89.90, 4},
    {"TB-TT",                           "SW-32", {1, 1, 2021},  44.90, 7},
    {"Navette impériale",               "SW-33", {1, 2, 2021},  49.90, 5},
    {"Étoile de la mort",               "SW-37", {1, 3, 2021},  99.90, 2},
    {"Chasseur stellaire de Boba Fett", "SW-38", {1, 1, 2022},  54.90, 6},
};

void afficherObjet(const Objet *o)
{
    /* À compléter : nom aligné à gauche, référence, date jj/mm/aaaa, prix, stock */
    (void) o;
}

int main(void)
{
    for (int i = 0; i < NB_OBJETS; i++)
        afficherObjet(&catalogue[i]);
    /* À compléter : menu (ex. 6.2) */
    return 0;
}
