#define _POSIX_C_SOURCE 200809L   /* inet_ntop est POSIX : nécessaire avec -std=c17 */
/* R3.05 - Sujet 09 - Étape 7 : accepter les connexions (serveur itératif)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g serveurTCP-3.c -o serveurTCP-3
 * Arrêt       : Ctrl-C
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
#define TAILLE_FILE 5
#define LG_MESSAGE 256

int main(void)
{
    int socketEcoute = socket(AF_INET, SOCK_STREAM, 0);
    if (socketEcoute == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket créée avec succès ! (%d)\n", socketEcoute);

    /* Permet de relancer le serveur immédiatement après l'avoir arrêté
     * (sinon « bind: Address already in use » pendant l'état TIME_WAIT). */
    int oui = 1;
    if (setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEADDR, &oui, sizeof oui) == -1)
        perror("setsockopt");

    struct sockaddr_in pointDeRencontreLocal;
    memset(&pointDeRencontreLocal, 0, sizeof pointDeRencontreLocal);
    pointDeRencontreLocal.sin_family = AF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    pointDeRencontreLocal.sin_port = htons(PORT);
    if (bind(socketEcoute, (struct sockaddr *) &pointDeRencontreLocal,
             sizeof pointDeRencontreLocal) == -1) {
        perror("bind");
        close(socketEcoute);
        exit(EXIT_FAILURE);
    }
    printf("Socket attachée avec succès !\n");

    if (listen(socketEcoute, TAILLE_FILE) == -1) {
        perror("listen");
        close(socketEcoute);
        exit(EXIT_FAILURE);
    }
    printf("Socket placée en écoute passive ...\n");

    /* --- Début de l'étape n°7 : en théorie, un serveur attend indéfiniment --- */
    for (;;) {
        char messageEnvoi[LG_MESSAGE];
        char messageRecu[LG_MESSAGE];
        struct sockaddr_in pointDeRencontreDistant;
        socklen_t longueurAdresse = sizeof pointDeRencontreDistant; /* à réinitialiser à CHAQUE accept */

        printf("Attente d'une demande de connexion (quitter avec Ctrl-C)\n");
        int socketDialogue = accept(socketEcoute, (struct sockaddr *) &pointDeRencontreDistant,
                                    &longueurAdresse);           /* appel bloquant */
        if (socketDialogue == -1) {
            perror("accept");
            continue;                       /* une erreur sur un client n'arrête pas le serveur */
        }
        char ipClient[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &pointDeRencontreDistant.sin_addr, ipClient, sizeof ipClient);
        printf("Client connecté : %s:%u\n", ipClient, (unsigned) ntohs(pointDeRencontreDistant.sin_port));

        ssize_t lus = read(socketDialogue, messageRecu, sizeof messageRecu - 1);
        if (lus == -1) {
            perror("read");
        } else if (lus == 0) {
            fprintf(stderr, "La socket a été fermée par le client !\n");
        } else {
            messageRecu[lus] = '\0';
            printf("Message reçu : %s (%zd octets)\n", messageRecu, lus);
            snprintf(messageEnvoi, sizeof messageEnvoi, "ok\n");
            ssize_t ecrits = write(socketDialogue, messageEnvoi, strlen(messageEnvoi));
            if (ecrits == -1)
                perror("write");
            else
                printf("Message %s envoyé (%zd octets)\n", messageEnvoi, ecrits);
        }
        close(socketDialogue);              /* on ferme le dialogue et on attend le suivant */
    }
    /* --- Fin de l'étape n°7 (jamais atteinte) --- */
}
