/* R3.05 - Sujet 01 - Exercice 3 : le grand test des formats
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g formats.c -o formats
 * ATTENTION : une ligne est VOLONTAIREMENT fausse ; gcc doit la signaler.
 */
#include <stdio.h>

int main(void)
{
    int i = 23674;
    int j = -23674;
    long k = (1L << 32);
    double x = 1e-8 + 1000;
    char c = 'A';
    char *chaine = "chaine de caracteres";

    printf("impression de i :\n");
    printf("%d \t %u \t %o \t %x\n", i, (unsigned) i, (unsigned) i, (unsigned) i);
    printf("impression de j :\n");
    printf("%d \t %u \t %o \t %x\n", j, (unsigned) j, (unsigned) j, (unsigned) j);
    printf("impression de k :\n");
    printf("%d \t %o \t %x\n", k, k, k);                 /* volontairement faux ! */
    printf("%ld \t %lu \t %lo \t %lx\n", k, (unsigned long) k, (unsigned long) k, (unsigned long) k);
    printf("impression de x :\n");
    printf("%f \t %e \t %g\n", x, x, x);
    printf("%.2f \t %.2e\n", x, x);
    printf("%.20f \t %.20e\n", x, x);
    printf("impression de c :\n");
    printf("%c \t %d\n", c, c);
    printf("impression de chaine :\n");
    printf("%s \t %.10s\n", chaine, chaine);

    /* Question 4 : afficher ici les tailles avec %zu et sizeof */

    return 0;
}
