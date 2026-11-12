#define _POSIX_C_SOURCE 200809L   /* inet_pton est POSIX : nécessaire avec -std=c17 */
/* R3.05 - Sujet 09 - Étape 2 : connexion au serveur
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g clientTCP-2.c -o clientTCP-2
 * Usage       : ./clientTCP-2 [adresse IPv4] [port]     (défaut : 127.0.0.1 5000)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>        /* memset */
#include <unistd.h>        /* close */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>    /* struct sockaddr_in */
#include <arpa/inet.h>     /* htons, inet_pton */

#define PORT_DEFAUT 5000

int main(int argc, char *argv[])
{
    const char *ip = (argc > 1) ? argv[1] : "127.0.0.1";
    long port = (argc > 2) ? strtol(argv[2], NULL, 10) : PORT_DEFAUT;
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Port invalide\n");
        return EXIT_FAILURE;
    }

    int descripteurSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (descripteurSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);

    /* --- Début de l'étape n°2 --- */
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse = sizeof pointDeRencontreDistant;
    memset(&pointDeRencontreDistant, 0, longueurAdresse);
    pointDeRencontreDistant.sin_family = AF_INET;             /* AF_ pour les adresses */
    pointDeRencontreDistant.sin_port = htons((uint16_t) port); /* ordre réseau (big-endian) */
    if (inet_pton(AF_INET, ip, &pointDeRencontreDistant.sin_addr) != 1) {
        fprintf(stderr, "Adresse IPv4 invalide : %s\n", ip);
        close(descripteurSocket);
        exit(EXIT_FAILURE);
    }

    if (connect(descripteurSocket, (struct sockaddr *) &pointDeRencontreDistant,
                longueurAdresse) == -1) {
        perror("connect");
        close(descripteurSocket);
        exit(EXIT_FAILURE);
    }
    /* --- Fin de l'étape n°2 --- */
    printf("Connexion au serveur réussie avec succès !\n");

    close(descripteurSocket);
    return EXIT_SUCCESS;
}
