/**
 * @file main.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source centrale qui fait marcher le jeu
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "player.h"

/**
 * @brief La fonction qui réuni toutes les autres fonctions et structures
 *
 * @return int
 *
 * @pre -
 * @post -
 *
 * Cette fonction est le coeur du jeu Sokoban. Elle lit un fichier contenant un niveau
 * de jeu, elle charge ce niveau dans la structure appropriée @c grid. Elle affiche le
 * niveau chargé dans le terminal. Elle lit les entrées au clavier de l'utilisateur
 * pour bouger le joueur dans le niveau.
 */
int main()
{
    // on charge le niveau de jeu depuis un fichier
    grid *level = init_level("levels/level1.txt");
    char entry = '\0'; // on initialise le stockage pour les entrées de l'utilisateur
    bool run = true; // on initialise l'interrupteur de boucle
    // on continue le jeu tant que l'utilisateur n'a pas appuyé sur 'q'
    while (run)
    {
        // on affiche les messages sur comment interagir
        printf("\nAppuyez sur \"q\" pour quitter\n");
        printf("Appuyez sur \"h, j, k, l\" pour vous déplacer\n\n");
        // on affiche le niveau de jeu
        display(level);
        printf("Votre choix : ");
        // on récupère l'entrée de l'utilisateur
        scanf(" %c", &entry);
        // on décide ce qu'on va faire en fonction de l'entrée
        switch (entry)
        {
        // on quitte le jeu si l'entrée est 'q'
        case 'q':
            run = false;
            break;
        // on bouge le jouer dans le sens correspondant si l'entrée est 'h', 'j', 'k' ou 'l'
        case 'h':
        case 'j':
        case 'k':
        case 'l':
            move_player(level, entry);
            break;
        // on affiche un message si l'entrée n'est pas définie dans le programme
        default:
            printf("---> Cette touche n'a pas de fonctionnalité\n");
        }
    }
    // on désalloue la structure qui stockait le niveau
    free_level(level);
    return EXIT_SUCCESS;
}
