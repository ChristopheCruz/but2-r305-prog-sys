/* Sujet 07 - Exercice 4 : protocole « radio clandestine » (squelette à compléter).
 * Message = exactement LG_MSG octets : PID sur LG_PID caractères (justifié à droite),
 * un espace, puis un indicatif de 3 caractères.  Exemple : "  1234 ABC"
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g protocole_squelette.c -o protocole
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef LG_PID
#define LG_PID 6
#endif
#define LG_CODE 3
#define LG_MSG (LG_PID + 1 + LG_CODE)          /* 10 octets avec LG_PID = 6 */

/* Écrit exactement n octets (boucle sur les écritures partielles).
 * Renvoie 0 si tout est écrit, -1 en cas d'erreur. */
static int ecrireTout(int fd, const char *buf, size_t n)
{
    /* TODO */
    (void) fd; (void) buf; (void) n;
    return -1;
}

/* Lit exactement n octets. Renvoie n, 0 en fin de fichier, -1 en cas d'erreur
 * ou de message tronqué. */
static ssize_t lireExactement(int fd, char *buf, size_t n)
{
    /* TODO */
    (void) fd; (void) buf; (void) n;
    return -1;
}

/* Fabrique le message dans msg (taille LG_MSG + 1). Renvoie 0 si OK, -1 si le PID
 * ou le code ne tiennent pas dans le format (vérifiez la valeur de retour de snprintf !). */
static int encoder(char *msg, size_t taille, pid_t pid, const char *code)
{
    /* TODO : snprintf(msg, taille, "%*d %.3s", LG_PID, (int) pid, code) ... */
    (void) msg; (void) taille; (void) pid; (void) code;
    return -1;
}

/* Décode msg (LG_MSG octets + '\0'). Renvoie 0 si le message est valide, -1 sinon. */
static int decoder(const char *msg, int *pid, char code[LG_CODE + 1])
{
    /* TODO : sscanf avec une largeur de champ, et test de sa valeur de retour */
    (void) msg; (void) pid; (void) code;
    return -1;
}

static void ecrivain(int fdEcriture, const char *codes[], int nb)
{
    /* TODO : pour chaque code, encoder puis ecrireTout, avec un petit sleep */
    (void) fdEcriture; (void) codes; (void) nb;
}

static void lecteur(int fdLecture, pid_t pid1, pid_t pid2)
{
    /* TODO : lire des messages de LG_MSG octets jusqu'à la fin de fichier ;
     * messages de pid1 -> stdout, de pid2 -> stderr, sinon « message suspect ». */
    (void) fdLecture; (void) pid1; (void) pid2;
}

int main(void)
{
    /* TODO :
     * 1. créer le tube ;
     * 2. créer l'écrivain 1, puis l'écrivain 2 (le père mémorise leurs PID) ;
     * 3. créer le lecteur (il hérite des deux PID) ;
     * 4. le père ferme les deux extrémités et attend ses trois fils. */
    (void) ecrireTout; (void) lireExactement; (void) encoder; (void) decoder;
    (void) ecrivain; (void) lecteur;
    return EXIT_SUCCESS;
}
