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
    if (target == WALL || target == BOX || target == GOAL) {
        return;
    }
    G->game_grid[target_row][target_column] = G->game_grid[G->player.y][G->player.x];
    G->game_grid[G->player.y][G->player.x] = target;
    G->player.x = target_column;
    G->player.y = target_row;
}
