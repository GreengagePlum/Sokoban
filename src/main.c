/*
Sokoban is a terminal and GUI puzzle game
Copyright (C) 2022, 2023 Efe ERKEN

This file is part of Sokoban

Sokoban is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sokoban is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sokoban.  If not, see <https://www.gnu.org/licenses/>.

SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file main.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source centrale qui fait marcher le jeu
 * @version 0.7
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grid.h"
#include "player.h"
#include "sdl2.h"

// on declare les pointeurs de fonction pour passer de <ncurses.h> à SDL2 et vice versa
// facilement en fonction des options donnée en ligne de commande
// ces fonctions ont la portée globale pour pouvoir être utilisé dans d'autres fichiers source
void (*handle_init)() = NULL;
enum Event (*handle_event)() = NULL;
void (*handle_display)(grid *) = NULL;
void (*handle_quit)() = NULL;

/**
 * @brief La fonction qui réunit toutes les autres fonctions et structures
 *
 * @param [in] argc Le nombre d'arguments passé en ligne de commande
 * @param [in] argv Le contenu des arguments passé en ligne de commande
 * @return int
 *
 * @pre -
 * @post -
 *
 * Cette fonction est le coeur du jeu Sokoban. Elle lit un fichier contenant un niveau
 * de jeu, elle charge ce niveau dans la structure appropriée @c grid. Elle affiche le
 * niveau chargé avec le méthode d'affichage voulue. Elle lit les entrées au clavier
 * de l'utilisateur pour bouger le joueur dans le niveau. Elle quitte le jeu quand
 * le niveau est réussi.
 */
int main(int argc, char *argv[])
{
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "--console") == 0))
    {
        // on initialise les pointeurs de fonction pour l'affichage <ncurses.h>
        handle_init = display_ncurses_init;
        handle_event = event_ncurses;
        handle_display = display_ncurses_draw;
        handle_quit = display_ncurses_end;
    }
    else if (argc == 2 && strcmp(argv[1], "--sdl2") == 0)
    {
        // on initialise les pointeurs de fonction pour l'affichage SDL2
        handle_init = sdl_init;
        handle_event = event_sdl2;
        handle_display = display_sdl2;
        handle_quit = sdl_quit;
    }
    else
    {
        // on affiche un message d'erreur si l'utilisateur a mal donné les options de lancement
        printf("Utilisation :\n");
        printf("./sokoban [--console|--sdl2]\n");
        // on quitte le programme
        exit(1);
    }
    // on charge le niveau de jeu depuis un fichier
    grid *level = init_level("levels/level1.txt");
    // on initialise le système d'affichage de niveau
    handle_init();
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
    exit_routine(level);
    return EXIT_SUCCESS;
}
