/* R3.05 - Sujet 05 - Mission 6 : le coffre suspect (programme VOLONTAIREMENT fragile)
 * Compilation : gcc -std=c17 -Wall -Wextra -pedantic -g coffre_suspect.c -o coffre_suspect
 * Trouvez les trois défauts de sécurité de ce programme avant de le corriger.
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define CHEMIN "/tmp/coffre_lamae.txt"

int main(void)
{
    const char *secret = "code du coffre : 4-8-15-16-23-42\n";

    if (access(CHEMIN, F_OK) == 0) {               /* 1. le fichier existe-t-il déjà ? */
        fprintf(stderr, "Le coffre existe déjà\n");
        return EXIT_FAILURE;
    }
    /* ... ici, une fenêtre de temps entre la vérification et l'utilisation ... */
    int fd = open(CHEMIN, O_WRONLY | O_CREAT | O_TRUNC, 0666);   /* 2. et 3. ? */
    if (fd == -1) {
        perror(CHEMIN);
        return EXIT_FAILURE;
    }
    if (write(fd, secret, strlen(secret)) == -1)
        perror("write");
    close(fd);
    printf("Secret rangé dans %s\n", CHEMIN);
    return EXIT_SUCCESS;
}
