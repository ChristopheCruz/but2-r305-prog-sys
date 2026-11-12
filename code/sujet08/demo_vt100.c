#define _POSIX_C_SOURCE 200809L   /* convention R3.05 : fonctions POSIX en -std=c17 */
/* demo_vt100.c -- exemple de l'annexe (R3.05 Sujet 08)
 * gcc -std=c17 -Wall -Wextra -pedantic -g demo_vt100.c -o demo_vt100
 */
#include <stdio.h>
#include "vt100.h"

int main(void)
{
    printf(CLEARSCR);
    printf(BOLD);
    printf(GOTOYX, 3, 10);   // ligne 3, colonne 10
    printf("bonjour\n");
    printf(NORMAL);
    return 0;
}
