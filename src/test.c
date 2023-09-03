/*
Function tests for Sokoban
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
 * @file test.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source pour tester les fonctions avant de les inaugurer
 * @version 0.5
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "grid.h"
#include "player.h"
#include "sdl2.h"

int main01()
{
    /// Test des fonctions creer_level() et free_level() dans grid.c
    int row = 11;
    int column = 26;
    int goal = 2;

    grid *level = creer_level(row, column, goal);
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

int main02()
{
    /// Test de la fonction init_level() dans grid.c
    grid *level = init_level("levels/level1.txt");

    printf("Number of lines is: %d\n", level->row_number);
    printf("Number of columns is: %d\n", level->column_number);
    printf("Grid block at coordinates (9,5): %c\n", level->game_grid[5][9]);
    printf("Grid block at coordinates (7,2): %c\n", level->game_grid[2][7]);
    printf("Player coordinates at start: (%d, %d)\n", level->player.x, level->player.y);

    free_level(level);
    return 0;
}

int main03()
{
    /// Test de la fonction display() dans grid.c
    grid *level = init_level("levels/level1.txt");
    display(level);
    free_level(level);
    return 0;
}

int main04()
{
    /// Test de la fonction move_player() dans player.c
    grid *level = init_level("levels/level1.txt");
    char quitCar = '\0';
    while (quitCar != 'q')
    {
        printf("Appuyez sur \"q\" pour quitter\n");
        printf("Appuyez sur \"h, j, k, l\" pour vous déplacer\n\n");
        display(level);
        printf("Votre choix : ");
        scanf(" %c", &quitCar);
        if (quitCar == 'h' || quitCar == 'j' || quitCar == 'k' || quitCar == 'l')
        {
            move_player(level, quitCar);
        }
    }
    free_level(level);
    return 0;
}

int main05()
{
    /// Test de la famille de fonctions display() qui utilisent <ncurses.h>
    grid *level = init_level("levels/level1.txt");
    display_ncurses_init();
    char entry = '\0';
    bool run = true;
    while (run)
    {
        display_ncurses_draw(level);
        entry = display_ncurses_input();
        switch (entry)
        {
        case 'q':
            run = false;
            break;
        case 'h':
        case 'j':
        case 'k':
        case 'l':
            move_player(level, entry);
            break;
        default:
            display_ncurses_input_error();
        }
    }
    display_ncurses_end();
    free_level(level);
    return 0;
}

int main06()
{
    /// Test de la nouvelle bibliothèque d'affichage SDL2
    sdl_init();
    SDL_SetRenderDrawColor(context.renderer, 126, 126, 126, 255);
    SDL_RenderClear(context.renderer);
    for (int i = 0; i < 25; i++)
    {
        SDL_SetRenderDrawColor(context.renderer, i * 10, 0, 0, 255);
        SDL_Rect rect = {.x = i * 50, .y = i * 50, .w = 50, .h = 50};
        SDL_RenderFillRect(context.renderer, &rect);
    }
    SDL_RenderPresent(context.renderer);
    int quit = 0;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
    }
    sdl_quit();
    return 0;
}

int main07()
{
    /// Test de la fonction display_sdl2()
    sdl_init();
    grid *level = init_level("levels/level1.txt");
    display_sdl2(level);
    SDL_Event ev;
    int quit = 0;
    while (!quit)
    {
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_QUIT)
        {
            quit = 1;
        }
    }
    sdl_quit();
    return 0;
}

int main08()
{
    /// Test de la fonction event_sdl2()
    sdl_init();
    int quit = 0;
    while (!quit)
    {
        enum Event ev = event_sdl2();
        printf("L'évenement déclanché : %d\n", ev);
        if (ev == EVENT_QUIT)
        {
            quit = 1;
        }
    }
    sdl_quit();
    return 0;
}

int main09()
{
    /// Test de la fonction event_ncurses()
    display_ncurses_init();
    int quit = 0;
    while (!quit)
    {
        enum Event ev = event_ncurses();
        printw("L'évenement déclanché : %d\n", ev);
        refresh();
        if (ev == EVENT_QUIT)
        {
            quit = 1;
        }
    }
    display_ncurses_end();
    return 0;
}

int main10()
{
    /// Test de la fonction event()
    int quit = 0;
    while (!quit)
    {
        enum Event ev = event();
        printf("L'évenement déclanché : %d\n", ev);
        if (ev == EVENT_QUIT)
        {
            quit = 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    /// Test de l'interprétation des arguments de ligne de commande
    if (argc < 2)
    {
        printf("Trop peu d'arguments\n");
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "--sdl2") == 0)
        {
            printf("SDL2\n");
        }
        else if (strcmp(argv[1], "--console") == 0)
        {
            printf("Console\n");
        }
        else
        {
            printf("Option inconnue\n");
        }
    }
    else
    {
        printf("Trop d'arguments\n");
    }
}
