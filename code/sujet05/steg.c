/* R3.05 - Sujet 05 - Mission 5 : stéganographie (squelette)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g steg.c -o steg
 * Usage : ./steg cacher  secret porteur   (ajoute secret à la fin de porteur)
 *         ./steg extraire porteur sortie   (récupère le fichier caché)
 *
 * Format en fin de porteur :
 *   [ contenu d'origine ][ contenu caché (n octets) ][ "LAMAE05" + '\0' (8 octets) ][ n sur 8 octets, petit-boutiste ]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SIGNATURE "LAMAE05"          /* 7 caractères + '\0' = 8 octets */
#define TAILLE_SIG 8
#define TAILLE_PIED (TAILLE_SIG + 8) /* signature + taille */

/* Écrit v sur 8 octets, octet de poids faible en premier (indépendant de la machine). */
static int ecrireU64(FILE *f, uint64_t v)
{
    unsigned char o[8];
    for (int i = 0; i < 8; i++)
        o[i] = (unsigned char) (v >> (8 * i));
    return fwrite(o, 1, 8, f) == 8 ? 0 : -1;
}

/* Relit une valeur écrite par ecrireU64. */
static int lireU64(FILE *f, uint64_t *v)
{
    unsigned char o[8];
    if (fread(o, 1, 8, f) != 8)
        return -1;
    *v = 0;
    for (int i = 7; i >= 0; i--)
        *v = (*v << 8) | o[i];
    return 0;
}

static int cacher(const char *secret, const char *porteur)
{
    /* TODO : ouvrir secret en "rb", porteur en "ab" ; copier secret à la fin de
     * porteur en comptant les octets ; écrire la signature puis la taille. */
    (void) secret; (void) porteur; (void) ecrireU64;
    return -1;
}

static int extraire(const char *porteur, const char *sortie)
{
    /* TODO : ouvrir porteur en "rb" ; se placer TAILLE_PIED octets avant la fin ;
     * lire et VÉRIFIER la signature ; lire la taille n et la VALIDER
     * (n <= taille du fichier - TAILLE_PIED) ; se placer au début du contenu caché ;
     * recopier n octets dans sortie. */
    (void) porteur; (void) sortie; (void) lireU64;
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage : %s cacher secret porteur | extraire porteur sortie\n", argv[0]);
        return EXIT_FAILURE;
    }
    int r;
    if (strcmp(argv[1], "cacher") == 0)
        r = cacher(argv[2], argv[3]);
    else if (strcmp(argv[1], "extraire") == 0)
        r = extraire(argv[2], argv[3]);
    else {
        fprintf(stderr, "Commande inconnue : %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    return r == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
