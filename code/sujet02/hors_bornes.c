/* R3.05 - Sujet 02 - Mission 2.1 : programme VOLONTAIREMENT faux (accès hors bornes).
 * Compiler une fois normalement, puis avec -fsanitize=address -g, et observer. */
#include <stdio.h>
#define N 5

int main(void)
{
    int secret = 1977;
    int tab[N] = {10, 20, 30, 40, 50};
    for (int i = 0; i <= N; i++)        /* erreur volontaire : <= au lieu de < */
        printf("tab[%d] = %d\n", i, tab[i]);
    tab[N + 2] = 0;                     /* écriture hors du tableau ! */
    printf("secret = %d\n", secret);
    return 0;
}
