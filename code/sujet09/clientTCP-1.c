/* R3.05 - Sujet 09 - Étape 1 : création d'une socket (côté client)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g clientTCP-1.c -o clientTCP-1
 */
#include <stdio.h>
#include <stdlib.h>        /* exit, EXIT_FAILURE */
#include <unistd.h>        /* close */
#include <sys/types.h>
#include <sys/socket.h>    /* socket */

int main(void)
{
    /* --- Début de l'étape n°1 : créer une socket de communication --- */
    /* AF_INET : IPv4 ; SOCK_STREAM : mode connecté ; 0 : protocole par défaut (TCP) */
    int descripteurSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (descripteurSocket == -1) {          /* toujours tester le retour */
        perror("socket");
        exit(EXIT_FAILURE);
    }
    /* --- Fin de l'étape n°1 --- */
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);

    close(descripteurSocket);               /* on rend la ressource */
    return EXIT_SUCCESS;
}
