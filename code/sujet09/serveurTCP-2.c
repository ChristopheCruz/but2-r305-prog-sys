/* R3.05 - Sujet 09 - Étape 6 : mise en écoute passive (listen)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g serveurTCP-2.c -o serveurTCP-2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define TAILLE_FILE 5    /* demandes de connexion en attente non encore acceptées */

int main(void)
{
    int socketEcoute = socket(AF_INET, SOCK_STREAM, 0);
    if (socketEcoute == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket créée avec succès ! (%d)\n", socketEcoute);

    struct sockaddr_in pointDeRencontreLocal;
    socklen_t longueurAdresse = sizeof pointDeRencontreLocal;
    memset(&pointDeRencontreLocal, 0, longueurAdresse);
    pointDeRencontreLocal.sin_family = AF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    pointDeRencontreLocal.sin_port = htons(PORT);
    if (bind(socketEcoute, (struct sockaddr *) &pointDeRencontreLocal, longueurAdresse) == -1) {
        perror("bind");
        close(socketEcoute);
        exit(EXIT_FAILURE);
    }
    printf("Socket attachée avec succès !\n");

    /* --- Début de l'étape n°6 --- */
    if (listen(socketEcoute, TAILLE_FILE) == -1) {
        perror("listen");
        close(socketEcoute);
        exit(EXIT_FAILURE);
    }
    /* --- Fin de l'étape n°6 --- */
    printf("Socket placée en écoute passive ...\n");

    close(socketEcoute);
    return EXIT_SUCCESS;
}
