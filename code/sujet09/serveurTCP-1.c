/* R3.05 - Sujet 09 - Étape 5 : création et attachement (bind) de la socket d'écoute
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g serveurTCP-1.c -o serveurTCP-1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>        /* close, sleep */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>    /* struct sockaddr_in, INADDR_ANY */
#include <arpa/inet.h>     /* htons, htonl */

#define PORT 5000

int main(void)
{
    int socketEcoute = socket(AF_INET, SOCK_STREAM, 0);
    if (socketEcoute == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket créée avec succès ! (%d)\n", socketEcoute);

    /* --- Début de l'étape n°5 --- */
    struct sockaddr_in pointDeRencontreLocal;
    socklen_t longueurAdresse = sizeof pointDeRencontreLocal;
    memset(&pointDeRencontreLocal, 0, longueurAdresse);
    pointDeRencontreLocal.sin_family = AF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); /* toutes les interfaces */
    pointDeRencontreLocal.sin_port = htons(PORT);

    if (bind(socketEcoute, (struct sockaddr *) &pointDeRencontreLocal, longueurAdresse) == -1) {
        perror("bind");
        close(socketEcoute);
        exit(EXIT_FAILURE);
    }
    /* --- Fin de l'étape n°5 --- */
    printf("Socket attachée avec succès !\n");

    sleep(2);                    /* le temps de lancer une seconde instance (cf. test) */
    close(socketEcoute);
    return EXIT_SUCCESS;
}
