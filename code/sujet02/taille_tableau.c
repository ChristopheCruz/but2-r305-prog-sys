/* R3.05 - Sujet 02 - Mission 2.2 : le sizeof qui ment.
 * gcc doit afficher un avertissement (-Wsizeof-array-argument) : lisez-le ! */
#include <stdio.h>

void afficherTaille(int tab[])
{
    printf("dans la fonction : %zu éléments\n", sizeof tab / sizeof tab[0]);
}

int main(void)
{
    int tab[10] = {0};
    printf("dans main : %zu éléments\n", sizeof tab / sizeof tab[0]);
    afficherTaille(tab);
    return 0;
}
