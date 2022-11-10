#ifndef GRID_HEADER
#define GRID_HEADER

#include "player.h"

enum CaseType
{
    WALL = '#',
    BOX = '$',
    PLAYER = '@',
    GOAL = '.',
    NONE = ' ',
    BOX_GOAL = '*',
    PLAYER_GOAL = '+'
};

/**
 * @struct Grid grid.h
 * @brief Cette structure contient les informations
 * concernant la grille du jeu et son contenu
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
