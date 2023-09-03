/*
Game movement management functions for Sokoban
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
 * @file player.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source contenant la fonction pour traiter le mouvement du joueur
 * @version 0.4
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "grid.h"

/**
 * @brief Fonction qui bouge le joueur dans la direction voulue dans le niveau
 *
 * @param [in,out] G Pointeur sur la structure du niveau pour lire les cases de celui-ci et les modifier
 * @param [in] D Une direction entre le haut, le bas, la gauche et la droite
 *
 * @pre @a G doit être non @c NULL et pointer sur la structure allouée
 * @post Modification de la structure pointée par @a G
 *
 * Cette fonction prend en paramètre deux arguments tels qu'un pointeur vers la structure
 * du niveau de jeu et une direction. Elle bouge le joueur dans la direction donnée si possible
 * en mettant à jour les cases du niveau dans la structure. Elle suit aussi la trace des objectifs réussis
 * du niveau en incrémentant et décrémentant en fonction du nombre de superpositions de boite et
 * d'objectif. Si dans la direction voulue, il n'y a pas de mur il y a plusieurs possibilités.
 * Si dans la direction il y a du vide ou un objectif,
 * elle change la case dans cette direction par un joueur ou une superposition de joueur et d'objectif
 * si la case cible est un objectif et elle change la case où était le joueur auparavant par du vide ou
 * un objectif si la case était une superposition de joueur et d'objectif avant. Si dans la direction
 * voulue il y a une boite, elle vérifie la deuxième case dans la direction. Si cette case est un mur,
 * une boite ou une superposition de boite et d'objectif alors il y a rien à faire. Pourtant si cette
 * case est du vide ou un objectif la fonction change cette case en une boite ou une superposition de
 * boite et d'objectif en fonction de cette case, elle bouge le joueur dans la case où était la boite.
 * Pour ce faire elle change l'ancien case de la boite par un joueur ou une superposition de joueur et d'objectif
 * en fonction de l'ancien état de la boite. Finalement, l'anicen case du joueur est changé en du vide ou
 * en un objectif en fonction de l'état ancien du joueur.
 */
void move_player(grid* G, enum Direction D) {
    int target_row = G->player.y, target_column = G->player.x;
    switch (D) {
        case LEFT:
            target_column--;
            break;
        case BOTTOM:
            target_row++;
            break;
        case TOP:
            target_row--;
            break;
        case RIGHT:
            target_column++;
    }
    enum CaseType target = G->game_grid[target_row][target_column];
    enum CaseType player = G->game_grid[G->player.y][G->player.x];
    if (target == WALL) {
        return;
    } else if (target == BOX) {
        int box_target_row = target_row + (target_row - G->player.y);
        int box_target_column = target_column + (target_column - G->player.x);
        enum CaseType box_target = G->game_grid[box_target_row][box_target_column];
        if (box_target == WALL || box_target == BOX || box_target == BOX_GOAL) {
            return;
        } else if (box_target == GOAL) {
            G->game_grid[box_target_row][box_target_column] = BOX_GOAL;
            G->game_grid[target_row][target_column] = PLAYER;
            if (player == PLAYER) {
                G->game_grid[G->player.y][G->player.x] = NONE;
            } else if (player == PLAYER_GOAL) {
                G->game_grid[G->player.y][G->player.x] = GOAL;
            }
            G->box_over_goal_number++;
        } else if (box_target == NONE) {
            G->game_grid[box_target_row][box_target_column] = BOX;
            G->game_grid[target_row][target_column] = PLAYER;
            if (player == PLAYER) {
                G->game_grid[G->player.y][G->player.x] = NONE;
            } else if (player == PLAYER_GOAL) {
                G->game_grid[G->player.y][G->player.x] = GOAL;
            }
        } else {
            move_player_error(G);
        }
    } else if (target == BOX_GOAL) {
        int box_target_row = target_row + (target_row - G->player.y);
        int box_target_column = target_column + (target_column - G->player.x);
        enum CaseType box_target = G->game_grid[box_target_row][box_target_column];
        if (box_target == WALL || box_target == BOX || box_target == BOX_GOAL) {
            return;
        } else if (box_target == GOAL) {
            G->game_grid[box_target_row][box_target_column] = BOX_GOAL;
            G->game_grid[target_row][target_column] = PLAYER_GOAL;
            if (player == PLAYER) {
                G->game_grid[G->player.y][G->player.x] = NONE;
            } else if (player == PLAYER_GOAL) {
                G->game_grid[G->player.y][G->player.x] = GOAL;
            }
        } else if (box_target == NONE) {
            G->game_grid[box_target_row][box_target_column] = BOX;
            G->game_grid[target_row][target_column] = PLAYER_GOAL;
            if (player == PLAYER) {
                G->game_grid[G->player.y][G->player.x] = NONE;
            } else if (player == PLAYER_GOAL) {
                G->game_grid[G->player.y][G->player.x] = GOAL;
            }
            G->box_over_goal_number--;
        } else {
            move_player_error(G);
        }
    } else if (target == GOAL) {
        G->game_grid[target_row][target_column] = PLAYER_GOAL;
        if (player == PLAYER) {
            G->game_grid[G->player.y][G->player.x] = NONE;
        } else if (player == PLAYER_GOAL) {
            G->game_grid[G->player.y][G->player.x] = GOAL;
        }
    } else if (target == NONE) {
        G->game_grid[target_row][target_column] = PLAYER;
        if (player == PLAYER) {
            G->game_grid[G->player.y][G->player.x] = NONE;
        } else if (player == PLAYER_GOAL) {
            G->game_grid[G->player.y][G->player.x] = GOAL;
        }
    } else {
        move_player_error(G);
    }
    G->player.x = target_column;
    G->player.y = target_row;
}

/**
 * @brief Fonction qui affiche un message d'erreur et quitte le jeu
 *
 * @param [in,out] G Pointeur sur une structure @c grid qui est le niveau de jeu
 *
 * @pre Avoir initialisé la structure de jeu @a G
 * @pre Avoir appelé @c handle_init() auparavant
 * @post -
 *
 * Cette fonction execute la routine de fin, affiche un message d'erreur pour le cas où le
 * jeu rencontre un caractère inconnu dans le niveau et quitte le jeu immédiatement.
 */
void move_player_error(grid* G) {
    exit_routine(G);
    fprintf(stderr, "Error, this level map has features unmanaged by the game\n");
    exit(1);
}
