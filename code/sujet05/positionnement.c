/* R3.05 - Sujet 05 - Exemple du cours : fwrite/fread, fseek, ftell, rewind
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g positionnement.c -o positionnement
 */
#include <stdio.h>
#include <stdlib.h>

#define NB 50
#define F_SORTIE "tresor.bin"

int main(void)
{
    FILE *fIn, *fOut;
    int *tab = malloc(NB * sizeof *tab);
    if (tab == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < NB; i++)
        tab[i] = i;

    /* écriture du tableau dans F_SORTIE (mode binaire : "wb") */
    if ((fOut = fopen(F_SORTIE, "wb")) == NULL) {
        perror(F_SORTIE);
        free(tab);
        return EXIT_FAILURE;
    }
    if (fwrite(tab, sizeof *tab, NB, fOut) != NB)
        perror("fwrite");
    fclose(fOut);
    free(tab);

    /* lecture dans F_SORTIE */
    if ((fIn = fopen(F_SORTIE, "rb")) == NULL) {
        perror(F_SORTIE);
        return EXIT_FAILURE;
    }
    int i;
    fseek(fIn, 0, SEEK_END);                         /* fin du fichier */
    printf("position %ld\n", ftell(fIn));

    fseek(fIn, -10L * (long) sizeof(int), SEEK_END); /* 10 int en arrière */
    printf("position %ld", ftell(fIn));
    if (fread(&i, sizeof i, 1, fIn) == 1)
        printf("\t i = %d", i);

    rewind(fIn);                                     /* retour au début */
    printf("\nposition %ld", ftell(fIn));
    if (fread(&i, sizeof i, 1, fIn) == 1)
        printf("\t i = %d", i);

    fseek(fIn, 5L * (long) sizeof(int), SEEK_CUR);   /* 5 int en avant */
    printf("\nposition %ld", ftell(fIn));
    if (fread(&i, sizeof i, 1, fIn) == 1)
        printf("\t i = %d\n", i);

    fclose(fIn);
    return EXIT_SUCCESS;
}
