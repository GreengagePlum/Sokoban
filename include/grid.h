/*
Game level data structures for Sokoban
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

#ifndef GRID_HEADER
#define GRID_HEADER

/**
 * @file grid.h
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier header contenant les structures de données pour traiter les niveaux du jeu sokoban
 * @version 0.7
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
 *
 */

#include "player.h"

/**
 * @brief Structure indiquant quel caractère correspond à quel élément du niveau
 *
 * Cette énumération indique les caractères symboliques du niveau qui sont
 * gérés par le jeu. Dans ce jeu sokoban, il y a des murs, des boites, un joueur,
 * des objectifs et du vide. Il y a deux caractères symboliques de plus pour indiquer
 * la superposition d'une boite ou d'un joueur avec un objectif.
 */
enum CaseType
{
    WALL = '#',       ///< Un mur
    BOX = '$',        ///< Une boîte
    PLAYER = '@',     ///< Le joueur
    GOAL = '.',       ///< Les objectifs
    NONE = ' ',       ///< Le vide
    BOX_GOAL = '*',   ///< Superposition d'une boîte et d'un objectif
    PLAYER_GOAL = '+' ///< Superposition d'un joueur et d'un objectif
};

/**
 * @brief Structure indiquant les différents événements dans le jeu
 *
 * Cette énumération indique les 6 interactions possibles dans le jeu :
 * quitter le jeu, aller à gauche, aller en bas, aller en haut, aller
 * à droite et rien faire.
 */
enum Event
{
    EVENT_QUIT,  ///< Quitter le jeu
    EVENT_LEFT,  ///< Bouger le joueur vers la gauche
    EVENT_DOWN,  ///< Bouger le joueur vers le bas
    EVENT_UP,    ///< Bouger le joueur vers le haut
    EVENT_RIGHT, ///< Bouger le jouer vers la droite
    EVENT_NONE   ///< Tout autre événement qui n'est pas géré dans le jeu
};

/**
 * @brief Cette structure contient les informations concernant le niveau du jeu et son contenu
 *
 * Une fois le jeu est lancé, le fichier contenant le niveau du jeu est chargé dans une instance
 * de cette structure. Les informations stocké sont les suivantes : chaque case du niveau,
 * nombre de lignes et colonnes, nombre d'objectifs du niveau et nombre d'objectifs réussi du niveau
 * ainsi que la position du joueur dans le niveau.
 */
typedef struct Grid
{
    enum CaseType **game_grid; ///< Tableau contenant les entités présents dans le jeu
    int column_number;         ///< Nombre de colonnes de game_grid
    int row_number;            ///< Nombre de lignes de game_grid
    int goal_number;           ///< Nombre d'objectifs de game_grid
    int box_over_goal_number;  ///< Nombre d'objectifs réussi de game_grid
    player player;             ///< Structure pour stocker la position du joueur
} grid;

// on déclare les pointeurs de fonctions pour pouvoir les utiliser
// dans les fonctions dans grid.c et player.c
extern void (*handle_init)();          ///< Fonction d'initialisation de <ncurses.h> ou SDL2
extern enum Event (*handle_event)();   ///< Fonction d'évènement de <ncurses.h> ou SDL2
extern void (*handle_display)(grid *); ///< Fonction d'affichage de <ncurses.h> ou SDL2
extern void (*handle_quit)();          ///< Fonction de fermeture de <ncurses.h> ou SDL2

grid *init_level(const char *file_path);

grid *creer_level(int row, int column, int goals);

void free_level(grid *G);

void display(grid *G);

void display_ncurses_init();

void display_ncurses_draw(grid *G);

char display_ncurses_input();

void display_ncurses_input_error();

void display_ncurses_end();

void display_sdl2(grid *G);

enum Event event();

enum Event event_ncurses();

enum Event event_sdl2();

void exit_routine(grid* G);

#endif
