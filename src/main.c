#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "player.h"

int main()
{
    grid *level = init_level("levels/level1.txt");
    char entry = '\0';
    bool run = true;
    while (run)
    {
        printf("\nAppuyez sur \"q\" pour quitter\n");
        printf("Appuyez sur \"h, j, k, l\" pour vous déplacer\n\n");
        display(level);
        printf("Votre choix : ");
        scanf(" %c", &entry);
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
            printf("---> Cette touche n'a pas de fonctionnalité\n");
        }
    }
    free_level(level);
    return EXIT_SUCCESS;
}
