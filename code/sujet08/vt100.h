/* vt100.h -- R3.05 Sujet 08 : séquences d'échappement VT100/ANSI
 * Les coordonnées commencent à 1 : (1,1) est le coin haut gauche.
 */
#ifndef VT100_H
#define VT100_H

/* Actions sur l'écran */
#define CLEARSCR      "\x1B[2J\x1B[;H"  // efface l'écran, curseur en (1,1)
#define CLEAREOL      "\x1B[K"          // efface jusqu'à la fin de la ligne
#define CLEAREOS      "\x1B[J"          // efface jusqu'à la fin de l'écran
#define CLEARLCR      "\x1B[0K"         // efface la ligne à droite du curseur
#define CLEARLCL      "\x1B[1K"         // efface la ligne à gauche du curseur
#define CLEARELN      "\x1B[2K"         // efface toute la ligne
#define CLEARCDW      "\x1B[0J"         // efface sous le curseur
#define CLEARCUP      "\x1B[1J"         // efface au-dessus du curseur
#define GOTOYX        "\x1B[%.2d;%.2dH" // printf(GOTOYX, ligne, colonne)
#define INSERTMOD     "\x1B[4h"         // mode insertion
#define OVERWRITEMOD  "\x1B[4l"         // mode remplacement
#define DELAFCURSOR   "\x1B[K"
#define CRLF          "\n\r"

/* Curseur */
#define CURSON        "\x1B[?25h"       // curseur visible
#define CURSOFF       "\x1B[?25l"       // curseur invisible

/* Attributs des caractères */
#define NORMAL        "\x1B[0m"
#define BOLD          "\x1B[1m"
#define UNDERLINE     "\x1B[4m"
#define BLINKING      "\x1B[5m"
#define INVVIDEO      "\x1B[7m"

/* Couleurs (bonus) : premier plan 30 à 37 */
#define FG_RED        "\x1B[31m"
#define FG_GREEN      "\x1B[32m"
#define FG_YELLOW     "\x1B[33m"
#define FG_BLUE       "\x1B[34m"
#define FG_MAGENTA    "\x1B[35m"
#define FG_CYAN       "\x1B[36m"

#endif
