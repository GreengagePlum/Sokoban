#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "grid.h"
#include "player.h"

grid *creer_grid(int row, int column)
{
    grid *G = (grid *)malloc(sizeof(grid));
    if (G == NULL)
    {
        fprintf(stderr, "Error G structure alloc failed");
        exit(-1);
    }
    G->game_grid = (enum CaseType **)(malloc(row * (sizeof(enum CaseType *))));
    if (G->game_grid == NULL)
    {
        fprintf(stderr, "Error game_grid row alloc failed");
        exit(-1);
    }
    for (int i = 0; i < row; i++)
    {
        G->game_grid[i] = (enum CaseType *)(malloc(column * (sizeof(enum CaseType))));
        if (G->game_grid[i] == NULL)
        {
            fprintf(stderr, "Error game_grid column alloc failed");
            exit(-1);
        }
    }
    G->row_number = row;
    G->column_number = column;
    return G;
}

void free_grid(grid *G)
{
    for (int i = 0; i < G->row_number; i++)
    {
        free(G->game_grid[i]);
    }
    free(G->game_grid);
    free(G);
}

grid *init_level(const char *file_path)
{
    // ouverture du fichier en mode lecture
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        fprintf(stderr, "Error %s not found", file_path);
        exit(-1);
    }
    char line[100] = {0};
    int number_column = 0; // nombre de colonne
    int number_row = 0;    /// nombre de ligne
    int number_goals = 0;
    // on lit la première ligne du fichier
    fgets(line, 100, file);
    sscanf(line, "%d %d %d", &number_column, &number_row, &number_goals);

    grid *level = creer_grid(number_row, number_column);

    int current_row = 0;
    // int current_goal = 0;
    // On lit le fichier ligne par ligne jusqu'à la fin du fichier
    while (fgets(line, 100, file) != NULL)
    {
        char *buffer = line;
        int current_column = 0;
        while (*buffer && *buffer != '\n')
        {
            level->game_grid[current_row][current_column] = *buffer;
            if (*buffer == '@') {
                level->player.x = current_column;
                level->player.y = current_row;
            }

            current_column += 1;
            buffer += 1;
        }
        current_row += 1;
    }
    // fermeture du fichier
    fclose(file);
    return level;
}

void display(grid *G) {
    for (int row = 0; row < G->row_number; row++) {
        for (int column = 0; column < G->column_number; column++) {
            printf("%c", G->game_grid[row][column]);
        }
        printf("\n");
    }
}

char display_ncurses(grid *G) {
    initscr();
    clear();
    noecho();
    cbreak();
    printw("Appuyez sur \"q\" pour quitter\n");
    printw("Appuyez sur \"h, j, k, l\" pour vous déplacer\n\n");
    for (int row = 0; row < G->row_number; row++) {
        for (int column = 0; column < G->column_number; column++) {
            printw("%c", G->game_grid[row][column]);
        }
        printw("\n");
    }
    refresh();
    char quitCar = '\0';
    while (quitCar != 'q' && quitCar != 'h' && quitCar != 'j' && quitCar != 'k' && quitCar != 'l') {
        quitCar = (char) getch();
    }
    endwin();
    return quitCar;
}
