/**
 * @file main.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source centrale qui fait marcher le jeu
 * @version 0.4
 * @date 2022-12-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "player.h"
#include "sdl2.h"

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
    // on initialise deux pointeurs de fonction pour passer de <ncurses.h> à SDL2 et vice versa facilement
    enum Event (*handle_event)() = event_sdl2;
    void (*handle_display)(grid *) = display_sdl2;
    // on charge le niveau de jeu depuis un fichier
    grid *level = init_level("levels/level1.txt");
    // on initialise le système d'affichage de niveau
    // display_ncurses_init();
    sdl_init();
    bool run = true; // on initialise l'interrupteur de boucle
    // on continue le jeu tant que l'utilisateur n'a pas quitté le jeu
    while (run)
    {
        // on affiche le niveau de jeu
        handle_display(level);
        // on récupère l'événement de l'utilisateur
        enum Event event = handle_event();
        // on décide ce qu'on va faire en fonction de l'événement
        switch (event)
        {
        case EVENT_NONE:
            break;
        // on quitte le jeu si événement = quitter le jeu
        case EVENT_QUIT:
            run = false;
            break;
        // on bouge le jouer dans le sens correspondant si événement = bouger dans un sens
        case EVENT_LEFT:
            move_player(level, LEFT);
            break;
        case EVENT_DOWN:
            move_player(level, BOTTOM);
            break;
        case EVENT_UP:
            move_player(level, TOP);
            break;
        case EVENT_RIGHT:
            move_player(level, RIGHT);
            break;
        }
        // on termine le jeu si tous les objectifs sont réussis
        if (level->goal_number == level->box_over_goal_number)
        {
            run = false;
        }
    }
    // on referme le système d'affichage de niveau pour désallouer la mémoire qu'il utilisait
    // display_ncurses_end();
    sdl_quit();
    // on désalloue la structure qui stockait le niveau
    free_level(level);
    return EXIT_SUCCESS;
}
