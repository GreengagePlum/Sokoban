#ifndef PLAYER_HEADER
#define PLAYER_HEADER

struct Grid;
typedef struct Grid grid;

typedef struct Player {
    int x;
    int y;
} player;

enum Direction {
    LEFT = 'h',
    BOTTOM = 'j',
    TOP = 'k',
    RIGHT = 'l'
};

void move_player(grid* G, enum Direction D);

#endif
