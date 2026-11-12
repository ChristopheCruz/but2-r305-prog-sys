/* R3.05 - Sujet 09 - Mission 4 : audit de sécurité
 *
 * Le « guichet d'accueil » du LAMAE, écrit à la va-vite par un stagiaire.
 * Protocole : le client envoie   TAILLE n\n   puis exactement n octets (son pseudo).
 *             Le serveur répond  Bienvenue <pseudo> (visiteur numero k)\n
 *
 * CE PROGRAMME CONTIENT VOLONTAIREMENT PLUSIEURS FAILLES. Ne l'exposez jamais sur le réseau :
 * il n'écoute que sur 127.0.0.1.
 *
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g -fsanitize=address serveur_naif.c -o serveur_naif
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5060

static int visiteurs = 0;

static void accueillir(int fd)
{
    char entete[32];
    char pseudo[16];
    char reponse[64];
    int n;

    read(fd, entete, sizeof entete);                 /* (a) */
    if (sscanf(entete, "TAILLE %d", &n) != 1)
        return;
    read(fd, pseudo, n);                             /* (b) */
    visiteurs++;
    sprintf(reponse, "Bienvenue %s (visiteur numero %d)\n", pseudo, visiteurs);   /* (c) */
    write(fd, reponse, strlen(reponse));             /* (d) */
}

int main(void)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in local;
    memset(&local, 0, sizeof local);
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_LOOPBACK);     /* 127.0.0.1 uniquement */
    local.sin_port = htons(PORT);
    bind(s, (struct sockaddr *) &local, sizeof local);
    listen(s, 5);
    for (;;) {
        int fd = accept(s, NULL, NULL);
        accueillir(fd);
        close(fd);
    }
}
