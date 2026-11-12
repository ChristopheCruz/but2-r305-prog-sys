/* R3.05 - Sujet 05 - Mission 4 : cp avec les appels système (squelette)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g cp_sys.c -o cp_sys
 * Usage       : ./cp_sys source destination [taille_tampon]
 */
#define _POSIX_C_SOURCE 200809L   /* AVANT tout #include : déclare les fonctions POSIX */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      /* open, O_RDONLY, O_CREAT... */
#include <unistd.h>     /* read, write, close */
#include <sys/types.h>  /* ssize_t */

/* Écrit les nb octets de buf, même si write n'en écrit qu'une partie.
 * Renvoie 0 si tout est écrit, -1 en cas d'erreur. */
static int ecrireTout(int fd, const char *buf, size_t nb)
{
    /* TODO : boucler sur write tant qu'il reste des octets à écrire */
    (void) fd; (void) buf; (void) nb;
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage : %s source destination [taille_tampon]\n", argv[0]);
        return EXIT_FAILURE;
    }
    /* TODO 1 : ouvrir la source en lecture seule (tester -1, perror)          */
    /* TODO 2 : ouvrir la destination : O_WRONLY | O_CREAT | O_TRUNC, 0644      */
    /* TODO 3 : allouer le tampon (taille lue dans argv[3] avec strtol, bornée) */
    /* TODO 4 : boucle read -> ecrireTout jusqu'à read == 0 ; gérer read == -1  */
    /* TODO 5 : close des deux descripteurs (tester le retour), free           */
    (void) ecrireTout;
    return EXIT_SUCCESS;
}
