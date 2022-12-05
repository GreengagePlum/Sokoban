/**
 * @file main.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source centrale qui fait marcher le jeu
 * @version 0.3
 * @date 2022-12-05
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
    // on initialise le système d'affichage de niveau
    init_display();
    char entry = '\0'; // on initialise le stockage pour les entrées de l'utilisateur
    bool run = true; // on initialise l'interrupteur de boucle
    // on continue le jeu tant que l'utilisateur n'a pas appuyé sur 'q'
    while (run)
    {
        // on affiche le niveau de jeu
        draw_display(level);
        // on récupère l'entrée de l'utilisateur
        entry = input_display();
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
            error_input_display();
        }
        // on termine le jeu si tous les objectifs sont réussis
        if (level->goal_number == level->box_over_goal_number) {
            run = false;
        }
    }
    // on referme le système d'affichage de niveau pour désallouer la mémoire qu'il utilisait
    end_display();
    // on désalloue la structure qui stockait le niveau
    free_level(level);
    return EXIT_SUCCESS;
}
