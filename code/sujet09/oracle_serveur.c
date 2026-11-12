#define _POSIX_C_SOURCE 200809L   /* inet_pton, inet_ntop, MSG_NOSIGNAL : POSIX, requis en -std=c17 */
/* R3.05 - Sujet 09 - L'Oracle du LAMAE (serveur fourni, NE PAS MODIFIER pendant la mission 3)
 *
 * Serveur TCP itératif à protocole texte, une commande par ligne :
 *     AIDE | ENIGME n | REPONSE n mot | QUITTER          (n = 1 à 4)
 * Chaque réponse du serveur tient sur UNE ligne terminée par '\n'.
 *
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g oracle_serveur.c -o oracle_serveur
 * Lancement   : ./oracle_serveur [adresse IPv4 d'écoute] [port]   (défaut : 127.0.0.1 5050)
 *
 * Ce serveur sert aussi de MODÈLE de programmation réseau défensive : lisez-le après la mission.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_DEFAUT 5050
#define TAILLE_FILE 8
#define LG_LIGNE 128          /* longueur maximale d'une commande, '\n' compris */
#define DELAI_INACTIVITE 60   /* secondes avant de déconnecter un client muet */
#define ERREURS_MAX 10        /* contre la force brute */
#define NB_ENIGMES 4

static const char *const enigmes[NB_ENIGMES] = {
    "Quel appel systeme place une socket en ecoute passive ?",
    "Quel est l'ordre des octets sur le reseau (un mot, avec un tiret) ?",
    "Combien de numeros de port differents un champ de 16 bits peut-il coder (en decimal) ?",
    "Quel appel systeme renvoie la socket de dialogue d'un nouveau client ?",
};
/* Réponses acceptées (comparaison sans tenir compte de la casse) */
static const char *const reponses[NB_ENIGMES][2] = {
    {"listen", "listen()"}, {"big-endian", "gros-boutiste"}, {"65536", "65 536"}, {"accept", "accept()"},
};
/* Drapeaux chiffrés (XOR) : inutile de les chercher avec `strings` ! */
#define CLE 0xA5
static const unsigned char drapeaux[NB_ENIGMES][24] = {
    {0xe3,0xe9,0xe4,0xe2,0xde,0xe7,0xe4,0xe6,0xee,0xe9,0xea,0xe2,0xfa,0x90,0xd8},
    {0xe3,0xe9,0xe4,0xe2,0xde,0xed,0xf1,0xea,0xeb,0xf6,0xfa,0xf5,0xe4,0xf7,0xf1,0xea,0xf0,0xf1,0xd8},
    {0xe3,0xe9,0xe4,0xe2,0xde,0xf6,0xe0,0xec,0xff,0xe0,0xfa,0xe7,0xec,0xf1,0xf6,0xd8},
    {0xe3,0xe9,0xe4,0xe2,0xde,0xe1,0xec,0xe4,0xe9,0xea,0xe2,0xf0,0xe0,0xd8},
};

static void dechiffrer(int i, char *dst, size_t taille)
{
    size_t k = 0;
    while (k + 1 < taille && k < sizeof drapeaux[i] && drapeaux[i][k] != 0) {
        dst[k] = (char) (drapeaux[i][k] ^ CLE);
        k++;
    }
    dst[k] = '\0';
}

/* Envoie TOUT le texte : send peut n'en envoyer qu'une partie. MSG_NOSIGNAL évite
 * d'être tué par SIGPIPE si le client est parti (on récupère EPIPE à la place). */
static int envoyerTout(int fd, const char *texte)
{
    size_t reste = strlen(texte);
    while (reste > 0) {
        ssize_t n = send(fd, texte, reste, MSG_NOSIGNAL);
        if (n == -1) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        texte += n;
        reste -= (size_t) n;
    }
    return 0;
}

/* Lit une ligne (au plus taille-1 octets, '\n' retiré, '\r' toléré).
 * Retour : longueur lue, 0 = client parti, -1 = erreur ou délai dépassé, -2 = ligne trop longue
 * ou caractère interdit. Lecture octet par octet : simple et sûr (mais lent). */
static ssize_t lireLigne(int fd, char *buf, size_t taille)
{
    size_t n = 0;
    for (;;) {
        char c;
        ssize_t r = recv(fd, &c, 1, 0);
        if (r == 0)
            return 0;
        if (r == -1) {
            if (errno == EINTR)
                continue;
            return -1;                       /* EAGAIN/EWOULDBLOCK : délai d'inactivité */
        }
        if (c == '\n')
            break;
        if (c == '\r')
            continue;
        if (!isprint((unsigned char) c))
            return -2;                       /* on refuse les octets de contrôle */
        if (n + 1 >= taille)
            return -2;                       /* trop long : on ne déborde jamais */
        buf[n++] = c;
    }
    buf[n] = '\0';
    return (ssize_t) n;
}

static int egalSansCasse(const char *a, const char *b)
{
    while (*a && *b) {
        if (tolower((unsigned char) *a) != tolower((unsigned char) *b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

/* Dialogue complet avec un client ; renvoie quand le client part ou abuse. */
static void servirClient(int fd, const char *ipClient)
{
    char ligne[LG_LIGNE];
    char reponse[2 * LG_LIGNE];
    int erreurs = 0;

    envoyerTout(fd, "ORACLE LAMAE v1 - tapez AIDE\n");
    for (;;) {
        ssize_t lg = lireLigne(fd, ligne, sizeof ligne);
        if (lg == 0 || lg == -1)
            return;
        if (lg == -2) {
            envoyerTout(fd, "ERREUR ligne trop longue ou caractere interdit : au revoir\n");
            /* Fermer avec des données non lues provoquerait un RST qui peut détruire notre
             * message : on ferme d'abord notre sens d'émission, puis on purge (au plus 4 Kio). */
            shutdown(fd, SHUT_WR);
            char poubelle[512];
            for (int k = 0; k < 8 && recv(fd, poubelle, sizeof poubelle, 0) > 0; k++) {
            }
            return;
        }
        int num;
        char mot[32];
        char fin;
        if (egalSansCasse(ligne, "AIDE")) {
            snprintf(reponse, sizeof reponse, "COMMANDES : AIDE | ENIGME n | REPONSE n mot | QUITTER (n = 1 a %d)\n", NB_ENIGMES);
        } else if (egalSansCasse(ligne, "QUITTER")) {
            envoyerTout(fd, "AU REVOIR\n");
            return;
        } else if (sscanf(ligne, "ENIGME %d %c", &num, &fin) == 1) {   /* %c : refuse les restes */
            if (num < 1 || num > NB_ENIGMES)
                snprintf(reponse, sizeof reponse, "ERREUR numero hors limites\n");
            else
                snprintf(reponse, sizeof reponse, "ENIGME %d : %s\n", num, enigmes[num - 1]);
        } else if (sscanf(ligne, "REPONSE %d %31[^\n]", &num, mot) == 2) {  /* largeur bornée */
            if (num < 1 || num > NB_ENIGMES) {
                snprintf(reponse, sizeof reponse, "ERREUR numero hors limites\n");
            } else if (egalSansCasse(mot, reponses[num - 1][0]) || egalSansCasse(mot, reponses[num - 1][1])) {
                char drapeau[32];
                dechiffrer(num - 1, drapeau, sizeof drapeau);
                snprintf(reponse, sizeof reponse, "BRAVO %s\n", drapeau);
                printf("[%s] enigme %d resolue\n", ipClient, num);
            } else {
                erreurs++;
                snprintf(reponse, sizeof reponse, "FAUX (%d/%d)\n", erreurs, ERREURS_MAX);
            }
        } else {
            erreurs++;
            snprintf(reponse, sizeof reponse, "ERREUR commande inconnue (%d/%d)\n", erreurs, ERREURS_MAX);
        }
        if (envoyerTout(fd, reponse) == -1)
            return;
        if (erreurs >= ERREURS_MAX) {
            envoyerTout(fd, "TROP D'ERREURS : au revoir\n");
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    const char *ip = (argc > 1) ? argv[1] : "127.0.0.1";   /* écoute locale par défaut */
    long port = (argc > 2) ? strtol(argv[2], NULL, 10) : PORT_DEFAUT;
    if (port < 1024 || port > 65535) {
        fprintf(stderr, "Port invalide (1024-65535)\n");
        return EXIT_FAILURE;
    }

    int socketEcoute = socket(AF_INET, SOCK_STREAM, 0);
    if (socketEcoute == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }
    int oui = 1;
    if (setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEADDR, &oui, sizeof oui) == -1)
        perror("setsockopt");

    struct sockaddr_in local;
    memset(&local, 0, sizeof local);
    local.sin_family = AF_INET;
    local.sin_port = htons((uint16_t) port);
    if (inet_pton(AF_INET, ip, &local.sin_addr) != 1) {
        fprintf(stderr, "Adresse invalide : %s\n", ip);
        close(socketEcoute);
        return EXIT_FAILURE;
    }
    if (bind(socketEcoute, (struct sockaddr *) &local, sizeof local) == -1 ||
        listen(socketEcoute, TAILLE_FILE) == -1) {
        perror("bind/listen");
        close(socketEcoute);
        return EXIT_FAILURE;
    }
    printf("Oracle a l'ecoute sur %s:%ld (Ctrl-C pour arreter)\n", ip, port);
    fflush(stdout);

    for (;;) {
        struct sockaddr_in distant;
        socklen_t lg = sizeof distant;
        int fd = accept(socketEcoute, (struct sockaddr *) &distant, &lg);
        if (fd == -1) {
            if (errno != EINTR)
                perror("accept");
            continue;
        }
        struct timeval delai = {DELAI_INACTIVITE, 0};       /* contre le client muet */
        if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &delai, sizeof delai) == -1)
            perror("setsockopt SO_RCVTIMEO");
        char ipClient[INET_ADDRSTRLEN] = "?";
        inet_ntop(AF_INET, &distant.sin_addr, ipClient, sizeof ipClient);
        printf("[%s:%u] connexion\n", ipClient, (unsigned) ntohs(distant.sin_port));
        fflush(stdout);
        servirClient(fd, ipClient);
        close(fd);
        printf("[%s] deconnexion\n", ipClient);
        fflush(stdout);
    }
}
