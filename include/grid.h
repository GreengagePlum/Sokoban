#ifndef GRID_HEADER
#define GRID_HEADER

/**
 * @file grid.h
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier header contenant les structures de données pour traiter les niveaux du jeu sokoban
 * @version 0.5
 * @date 2022-12-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "player.h"

/**
 * @brief Structure indiquant quel caractère correspond à quel élément du niveau
 *
 * Cette énumération indique les caractères symboliques du niveau qui sont
 * gérés par le jeu. Dans ce jeu sokoban, il y a des murs, des boites, un joueur,
 * des objectifs et du vide. Il y a deux caractères symboliques de plus pour indiquer
 * la superposition d'une boite ou d'un joueur avec un objectif.
 */
enum CaseType
{
    WALL = '#',       ///< Un mur
    BOX = '$',        ///< Une boîte
    PLAYER = '@',     ///< Le joueur
    GOAL = '.',       ///< Les objectifs
    NONE = ' ',       ///< Le vide
    BOX_GOAL = '*',   ///< Superposition d'une boîte et d'un objectif
    PLAYER_GOAL = '+' ///< Superposition d'un joueur et d'un objectif
};

/**
 * @brief Structure indiquant les différents événements dans le jeu
 *
 * Cette énumération indique les 6 interactions possibles dans le jeu :
 * quitter le jeu, aller à gauche, aller en bas, aller en haut, aller
 * à droite et rien faire.
 */
enum Event
{
    EVENT_QUIT,  ///< Quitter le jeu
    EVENT_LEFT,  ///< Bouger le joueur vers la gauche
    EVENT_DOWN,  ///< Bouger le joueur vers le bas
    EVENT_UP,    ///< Bouger le joueur vers le haut
    EVENT_RIGHT, ///< Bouger le jouer vers la droite
    EVENT_NONE   ///< Tout autre événement qui n'est pas géré dans le jeu
};

/**
 * @brief Cette structure contient les informations concernant le niveau du jeu et son contenu
 *
 * Une fois le jeu est lancé, le fichier contenant le niveau du jeu est chargé dans une instance
 * de cette structure. Les informations stocké sont les suivantes : chaque case du niveau,
 * nombre de lignes et colonnes, nombre d'objectifs du niveau et nombre d'objectifs réussi du niveau
 * ainsi que la position du joueur dans le niveau.
 */
typedef struct Grid
{
    enum CaseType **game_grid; ///< Tableau contenant les entités présents dans le jeu
    int column_number;         ///< Nombre de colonnes de game_grid
    int row_number;            ///< Nombre de lignes de game_grid
    int goal_number;           ///< Nombre d'objectifs de game_grid
    int box_over_goal_number;  ///< Nombre d'objectifs réussi de game_grid
    player player;             ///< Structure pour stocker la position du joueur
} grid;

grid *init_level(const char *file_path);

grid *creer_level(int row, int column, int goals);

void free_level(grid *G);

void display(grid *G);

void display_ncurses_init();

void display_ncurses_draw(grid *G);

char display_ncurses_input();

void display_ncurses_input_error();

void display_ncurses_end();

void display_sdl2(grid *G);

enum Event event();

enum Event event_ncurses();

enum Event event_sdl2();

#endif
