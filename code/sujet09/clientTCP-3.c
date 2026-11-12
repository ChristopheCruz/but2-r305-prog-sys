#define _POSIX_C_SOURCE 200809L   /* inet_pton est POSIX : nécessaire avec -std=c17 */
/* R3.05 - Sujet 09 - Étape 4 : échange de données (client)
 * Protocole minimal : le client envoie une chaîne, le serveur répond.
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g clientTCP-3.c -o clientTCP-3
 * Usage       : ./clientTCP-3 [adresse IPv4] [port]     (défaut : 127.0.0.1 5000)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>        /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_DEFAUT 5000
#define LG_MESSAGE 256

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

    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse = sizeof pointDeRencontreDistant;
    memset(&pointDeRencontreDistant, 0, longueurAdresse);
    pointDeRencontreDistant.sin_family = AF_INET;
    pointDeRencontreDistant.sin_port = htons((uint16_t) port);
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
    printf("Connexion au serveur réussie avec succès !\n");

    /* --- Début de l'étape n°4 --- */
    char messageEnvoi[LG_MESSAGE];
    char messageRecu[LG_MESSAGE];

    snprintf(messageEnvoi, sizeof messageEnvoi, "Hello world !\n");   /* borné */
    ssize_t ecrits = write(descripteurSocket, messageEnvoi, strlen(messageEnvoi));
    if (ecrits == -1) {
        perror("write");
        close(descripteurSocket);
        exit(EXIT_FAILURE);
    }
    printf("Message %s envoyé avec succès (%zd octets)\n", messageEnvoi, ecrits);

    /* On lit AU PLUS LG_MESSAGE - 1 octets pour garder la place du '\0' final */
    ssize_t lus = read(descripteurSocket, messageRecu, sizeof messageRecu - 1);
    switch (lus) {
    case -1:
        perror("read");
        close(descripteurSocket);
        exit(EXIT_FAILURE);
    case 0:
        fprintf(stderr, "La socket a été fermée par le serveur !\n");
        break;
    default:
        messageRecu[lus] = '\0';          /* read ne termine PAS la chaîne */
        printf("Message reçu du serveur : %s (%zd octets)\n", messageRecu, lus);
    }
    /* --- Fin de l'étape n°4 --- */

    close(descripteurSocket);
    return EXIT_SUCCESS;
}
