#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "player.h"

int main01()
{
    // Test des fonctions creer_level() et free_level() dans grid.c
    int row = 11;
    int column = 26;

    grid* level = creer_level(row, column);
    level->game_grid[0][0] = '#';
    level->game_grid[3][1] = '@';

    printf("Size of structure is %d\n", (int)sizeof(*level));
    printf("Number of lines is %d\n", level->row_number);
    printf("Number of columns is %d\n", level->column_number);
    printf("Grid block at coordinates (0,0) %c\n", level->game_grid[0][0]);
    printf("Grid block at coordinates (1,3) %c\n", level->game_grid[3][1]);

    free_level(level);
    return 0;
}

int main02() {
    // Test de la fonction init_level() dans grid.c
    grid* level = init_level("levels/level1.txt");

    printf("Number of lines is: %d\n", level->row_number);
    printf("Number of columns is: %d\n", level->column_number);
    printf("Grid block at coordinates (9,5): %c\n", level->game_grid[5][9]);
    printf("Grid block at coordinates (7,2): %c\n", level->game_grid[2][7]);
    printf("Player coordinates at start: (%d, %d)\n", level->player.x, level->player.y);

    free_level(level);
    return 0;
}

int main03() {
    // Test de la fonction display() dans grid.c
    grid* level = init_level("levels/level1.txt");
    display(level);
    free_level(level);
    return 0;
}

int main() {
    // Test de la fonction move_player() dans player.c
    grid* level = init_level("levels/level1.txt");
    char quitCar = '\0';
    while (quitCar != 'q') {
        printf("Appuyez sur \"q\" pour quitter\n");
        printf("Appuyez sur \"h, j, k, l\" pour vous déplacer\n\n");
        display(level);
        printf("Votre choix : ");
        scanf(" %c", &quitCar);
        if (quitCar == 'h' || quitCar == 'j' || quitCar == 'k' || quitCar == 'l') {
            move_player(level, quitCar);
        }
    }
    free_level(level);
    return 0;
}
