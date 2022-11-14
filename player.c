/**
 * @file player.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source contenant la fonction pour traiter le mouvement du joueur
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
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
 * en mettant à jour les cases du niveau dans la structure. Si dans la direction voulue, il n'y a
 * pas de mur ou de boite, alors elle change la case dans cette direction par un joueur ou une
 * superposition de joueur et d'objectif si la case cible est un objectif
 * et elle change la case où était le joueur auparavant par du vide ou un objectif si la case est
 * une superposition de joueur et d'objectif avant.
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
    if (target == WALL || target == BOX) {
        return;
    } else if (target == GOAL) {
        if (player == PLAYER) {
            G->game_grid[target_row][target_column] = PLAYER_GOAL;
            G->game_grid[G->player.y][G->player.x] = NONE;
        } else if (player == PLAYER_GOAL) {
            G->game_grid[target_row][target_column] = PLAYER_GOAL;
            G->game_grid[G->player.y][G->player.x] = GOAL;
        }
    } else if (target == NONE) {
        if (player == PLAYER) {
            G->game_grid[target_row][target_column] = PLAYER;
            G->game_grid[G->player.y][G->player.x] = NONE;
        } else if (player == PLAYER_GOAL) {
            G->game_grid[target_row][target_column] = PLAYER;
            G->game_grid[G->player.y][G->player.x] = GOAL;
        }
    } else {
        fprintf(stderr, "Error this level map has features unmanaged by the game\n");
        exit(-1);
    }
    G->player.x = target_column;
    G->player.y = target_row;
}
