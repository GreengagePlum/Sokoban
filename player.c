#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "grid.h"

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
