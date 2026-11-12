# R3.05 · Programmation système

**BUT2 Informatique · IUT Dijon-Auxerre · Université Bourgogne Europe · 2026-2027**
Enseignant : Christophe Cruz

Supports du module R3.05 : programmation système en C sous Linux (processus, fichiers, communication et synchronisation, ordonnancement, mémoire virtuelle).

## Contenu du dépôt

```
cours/    les diapositives des cours magistraux (PDF et PowerPoint)
sujets/   les sujets de TD/TP (PDF et Word)
code/     les fichiers de départ des TD/TP, rangés par sujet
```

## Cours magistraux

| CM | Thème | Fichier |
|----|-------|---------|
| 01a | Préambule, langage C, types, pointeurs | `cours/CM01a-preambule-et-langage-C` |
| 01b | Entrées-sorties standard, allocation dynamique | `cours/CM01b-entrees-sorties-et-allocation-dynamique` |
| 02 | Les fichiers : appels système, i-nœuds | `cours/CM02-les-fichiers` |
| 03a | Les processus : fork, exec, wait | `cours/CM03a-les-processus` |
| 03b | Tubes, redirections, concurrence | `cours/CM03b-tubes-et-concurrence` |
| 04 | Signaux et IPC | `cours/CM04-signaux-et-IPC` |
| 05 | Sémaphores, moniteurs, philosophes | `cours/CM05-semaphores-moniteurs-philosophes` |
| 06 | L'ordonnanceur | `cours/CM06-ordonnanceur` |
| 07a | Mémoire virtuelle (1/2) : MMU, segmentation, pile et tas | `cours/CM07a-memoire-virtuelle-1` |
| 07b | Mémoire virtuelle (2/2) : pagination, défauts de page, swap | `cours/CM07b-memoire-virtuelle-2` |

## TD/TP

| Sujet | Thème | Code de départ |
|-------|-------|----------------|
| 01 | Le langage C, partie 1 | `code/sujet01/` |
| 02 | Le langage C, partie 2 | `code/sujet02/` |
| 03 | Les pointeurs | `code/sujet03/` |
| 04 | L'allocation dynamique | `code/sujet04/` |
| 05 | Les fichiers | `code/sujet05/` |
| 06 | Les processus | `code/sujet06/` |
| 07 | Les tubes | `code/sujet07/` |
| 08 | Les threads et les mutex | `code/sujet08/` |
| 09 | Les sockets | `code/sujet09/` |

Chaque sujet dure 2 h. Les exercices sont notés de ★ à ★★★ ; un fil rouge propose des drapeaux `FLAG{...}` à découvrir.

## Compiler

La ligne de compilation utilisée dans tout le module :

```bash
gcc -std=c17 -Wall -Wextra -pedantic -g programme.c -o programme
```

- Les programmes qui utilisent des fonctions POSIX (`fork`, `pipe`, `sigaction`…) commencent par `#define _POSIX_C_SOURCE 200809L`.
- Avec les threads, ajoutez `-pthread`.
- Pour traquer les erreurs mémoire : `-fsanitize=address,undefined`, ou `valgrind --leak-check=full ./programme`.

Quelques fichiers de départ produisent des avertissements ou contiennent des erreurs **volontaires** : ce sont des supports d'exercice (par exemple `code/sujet09/serveur_naif.c`, vulnérable exprès pour l'exercice d'audit). Ne les réutilisez pas tels quels.

## Ressources

- Le manuel : `man 2 open`, `man 2 fork`, `man 7 signal`, `man 7 pipe`…
- [cppreference : la bibliothèque C](https://en.cppreference.com/w/c)
- [ANSSI : règles de programmation pour le développement sécurisé de logiciels en langage C](https://cyber.gouv.fr/publications/regles-de-programmation-pour-le-developpement-securise-de-logiciels-en-langage-c)
- M. Kerrisk, *The Linux Programming Interface*, No Starch Press
- A. Tanenbaum, *Systèmes d'exploitation*, Pearson
- R. et A. Arpaci-Dusseau, [*Operating Systems: Three Easy Pieces*](https://pages.cs.wisc.edu/~remzi/OSTEP/) (gratuit en ligne)

## Licences

- Diapositives et sujets (`cours/`, `sujets/`) : [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.fr), voir `LICENSE-supports.md`.
- Code (`code/`) : licence MIT, voir `LICENSE`.
