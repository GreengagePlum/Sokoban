#ifndef GRID_HEADER
#define GRID_HEADER

#include "player.h"

enum CaseType
{
    WALL = '#',
    BOX = '$',
    PLAYER = '@',
    GOAL = '.',
    NONE = ' '
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
    Player player;             ///< Structure pour stocker la position du joueur
} grid;

grid *init_level(const char *file_path);

grid *creer_grid(int row, int column);

void free_grid(grid *G);

void display_stdio(grid *G);

void display_ncurses(grid *G);

#endif
