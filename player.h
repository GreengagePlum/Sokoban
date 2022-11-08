#ifndef PLAYER_HEADER
#define PLAYER_HEADER

typedef struct player {
    int x;
    int y;
} Player;

enum Direction {
    LEFT = 'h',
    BOTTOM = 'j',
    TOP = 'k',
    RIGHT = 'l'
};



#endif
