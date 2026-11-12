/* Sujet 07 - Exemple 2 : deux écrivains, un lecteur, un seul tube.
 * ATTENTION : ce fichier reproduit FIDELEMENT l'exemple du cours ancien.
 * Il compile sans avertissement... mais contient au moins TROIS défauts
 * à trouver (Exercice 3). Ne le corrigez qu'après les avoir identifiés.
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g brouillage.c -o brouillage
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void f1(void), f2(void), f3(void);          /* les 3 fils */
static void (*tabFonct[3])(void) = { f1, f2, f3 };

static int p[2];
static char seq1[27] = "ABCDEFGHIJKILMOPQRSTUVWXYZ";   /* écrite par FILS1 */
static char seq2[27] = "abcdefghijklmnopqrstuvwxyz";   /* écrite par FILS2 */

int main(void)
{
    if (pipe(p) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 3; i++) {
        switch (fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            tabFonct[i]();
            exit(EXIT_SUCCESS);
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
}

static void f1(void)
{
    close(p[0]);
    for (int i = 0; i < 26; i += 3) {
        write(p[1], &seq1[i], 3);
        sleep(3);
    }
    close(p[1]);
}

static void f2(void)
{
    close(p[0]);
    for (int i = 0; i < 26; i += 3) {
        write(p[1], &seq2[i], 3);
        sleep(4);
    }
    close(p[1]);
}

static void f3(void)
{
    char s[5];
    close(p[1]);
    while (read(p[0], s, 4) > 0)
        printf("%s", s);
    close(p[0]);
    printf("\n");
}
