#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"

int main01()
{
    // Test des fonctions creer_grid() et free_grid() dans grid.c
    int row = 11;
    int column = 26;

    grid* level = creer_grid(row, column);
    level->game_grid[0][0] = '#';
    level->game_grid[3][1] = '@';

    printf("Size of structure is %d\n", (int)sizeof(*level));
    printf("Number of lines is %d\n", level->row_number);
    printf("Number of columns is %d\n", level->column_number);
    printf("Grid block at coordinates (0,0) %c\n", level->game_grid[0][0]);
    printf("Grid block at coordinates (1,3) %c\n", level->game_grid[3][1]);

    free_grid(level);
    return 0;
}

int main() {
    // Test de la fonction init_level() dans grid.c
    grid* level = init_level("level1.txt");

    printf("Number of lines is %d\n", level->row_number);
    printf("Number of columns is %d\n", level->column_number);
    printf("Grid block at coordinates (12,5) %c\n", level->game_grid[5][12]);
    printf("Grid block at coordinates (7,2) %c\n", level->game_grid[2][7]);

    free_grid(level);
    return 0;
}
