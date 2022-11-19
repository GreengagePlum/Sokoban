#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/**
 * @file player.h
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier header contenant les structures pour traiter le joueur et son mouvement
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

struct Grid;
typedef struct Grid grid;

/**
 * @brief Cette structure contient la position du joueur dans le niveau
 *
 * Cette structure a deux attributs pour stocker les coordonnées x et y du joueur
 */
typedef struct Player
{
    int x; ///< Coordonnée x du joueur
    int y; ///< Coordonnée y du joueur
} player;

/**
 * @brief Cette structure contient les directions possibles dans le jeu
 *
 * Cette structure indique une direction telle que les 4 possibles mais aussi
 * quelle touche du clavier correspond à quelle direction. Elle est utile pour
 * determiner le mouvement du joueur. Les touches pour controler le joueur
 * peuvent être changées ici.
 */
enum Direction
{
    LEFT = 'h',   ///< La direction gauche
    BOTTOM = 'j', ///< La direction basse
    TOP = 'k',    ///< La direction haute
    RIGHT = 'l'   ///< La direction droite
};

void move_player(grid *G, enum Direction D);

#endif
