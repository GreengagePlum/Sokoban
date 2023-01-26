/*
Player and player movement related data structures for Sokoban
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

#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/**
 * @file player.h
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier header contenant les structures pour traiter le joueur et son mouvement
 * @version 0.3
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
 *
 */

struct Grid;
typedef struct Grid grid;

/**
 * @brief Cette structure contient la position du joueur dans le niveau
 *
 * Cette structure a deux attributs pour stocker les coordonnées x et y du joueur
 */
typedef struct Player
{
    int x; ///< Coordonnée x du joueur
    int y; ///< Coordonnée y du joueur
} player;

/**
 * @brief Cette structure contient les directions possibles dans le jeu
 *
 * Cette structure indique une direction telle que les 4 possibles mais aussi
 * quelle touche du clavier correspond à quelle direction. Elle est utile pour
 * determiner le mouvement du joueur. Les touches pour controler le joueur
 * peuvent être changées ici.
 */
enum Direction
{
    LEFT = 'h',   ///< La direction gauche
    BOTTOM = 'j', ///< La direction basse
    TOP = 'k',    ///< La direction haute
    RIGHT = 'l'   ///< La direction droite
};

void move_player(grid *G, enum Direction D);

void move_player_error(grid* G);

#endif
