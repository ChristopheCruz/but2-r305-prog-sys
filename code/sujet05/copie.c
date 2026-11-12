/* R3.05 - Sujet 05 - Exemple du cours : copie caractère par caractère (stdio)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g copie.c -o copie
 */
#include <stdio.h>
#include <stdlib.h>

#define ENTREE "entree.txt"
#define SORTIE "sortie.txt"

int main(void)
{
    FILE *fIn, *fOut;
    int c;                                   /* int, pas char : EOF ! */

    if ((fIn = fopen(ENTREE, "r")) == NULL) {
        perror(ENTREE);                      /* message + raison (errno) sur stderr */
        return EXIT_FAILURE;
    }
    if ((fOut = fopen(SORTIE, "w")) == NULL) {
        perror(SORTIE);
        fclose(fIn);
        return EXIT_FAILURE;
    }
    while ((c = fgetc(fIn)) != EOF)
        fputc(c, fOut);

    fclose(fIn);
    if (fclose(fOut) == EOF) {               /* l'écriture réelle peut échouer ici */
        perror("fclose");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
