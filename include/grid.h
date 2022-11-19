#ifndef GRID_HEADER
#define GRID_HEADER

/**
 * @file grid.h
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier header contenant les structures de données pour traiter les niveaux du jeu sokoban
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
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
 * @brief Cette structure contient les informations concernant le niveau du jeu et son contenu
 *
 * Une fois le jeu est lancé, le fichier contenant le niveau du jeu est chargé dans une instance
 * de cette structure. Les informations stocké sont les suivantes : chaque case du niveau,
 * nombre de ligne et colonne ainsi que la position du joueur dans le niveau.
 */
typedef struct Grid
{
    enum CaseType **game_grid; ///< Tableau contenant les entités présents dans le jeu
    int column_number;         ///< Nombre de colonne de game_grid
    int row_number;            ///< Nomber de ligne de game_grid
    player player;             ///< Structure pour stocker la position du joueur
} grid;

grid *init_level(const char *file_path);

grid *creer_level(int row, int column);

void free_level(grid *G);

void display(grid *G);

void display_ncurses(grid *G);

#endif
