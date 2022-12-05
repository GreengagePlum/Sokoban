/**
 * @file grid.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source contenant les fonctions pour traiter les niveaux du jeu sokoban
 * @version 0.3
 * @date 2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "grid.h"
#include "player.h"

/**
 * @brief Fonction qui alloue la grille du jeu
 *
 * @param [in] row Le nombre de lignes du niveau de jeu
 * @param [in] column Le nombre de colonnes du niveau de jeu
 * @return grid*
 *
 * @pre -
 * @post -
 *
 * Cette fonction prend en paramètre trois arguments tels que le nombre de lignes,
 * le nombre de colonnes et le nombre d'objectifs du niveau de jeu. Elle alloue
 * dynamiquement la structure @c grid en fonction de cette taille et
 * renvoie un pointeur sur cette structure.
 */
grid *creer_level(int row, int column, int goals)
{
    // on alloue la structure elle-même dynamiquement
    grid *G = (grid *)malloc(sizeof(grid));
    // on vérifie si l'allocation s'est bien passée
    if (G == NULL)
    {
        fprintf(stderr, "Error game structure alloc failed");
        exit(-1);
    }
    // on alloue la première dimension du tableau dynamique à deux dimensions dans la structure
    G->game_grid = (enum CaseType **)(malloc(row * (sizeof(enum CaseType *))));
    // on vérifie si l'allocation s'est bien passée
    if (G->game_grid == NULL)
    {
        fprintf(stderr, "Error game_grid row alloc failed");
        exit(-1);
    }
    // on alloue la deuxième dimension du tableau dynamique
    for (int i = 0; i < row; i++)
    {
        G->game_grid[i] = (enum CaseType *)(malloc(column * (sizeof(enum CaseType))));
        // on vérifie si l'allocation s'est bien passée
        if (G->game_grid[i] == NULL)
        {
            fprintf(stderr, "Error game_grid column alloc failed");
            exit(-1);
        }
    }
    // on initialise les valeurs de taille et d'objectifs du niveau
    G->row_number = row;
    G->column_number = column;
    G->goal_number = goals;
    return G;
}

/**
 * @brief Fonction pour désallouer la structure du jeu
 *
 * @param [in] G Pointeur sur une structure @c grid
 *
 * @pre @a G doit être non @c NULL et pointer sur la structure allouée
 * @post @a G contient toujours l'adresse qu'il avait
 *
 * Cette fonction prend en paramètre un pointeur sur une structure @c grid
 * et désalloue cette structure. Pour cela dans un premier temps, elle
 * désalloue le tableau dynamique à deux dimensions @a game_grid et finalement
 * elle désalloue la structure elle-même.
 */
void free_level(grid *G)
{
    // on désalloue la deuxième dimension du tableau dynamique dans la structure
    for (int i = 0; i < G->row_number; i++)
    {
        free(G->game_grid[i]);
    }
    // on désalloue la première dimension du tableau dynamique
    free(G->game_grid);
    // on désalloue la structure
    free(G);
}

/**
 * @brief Fonction qui charge le niveau de jeu depuis un fichier dans la structure @c grid
 *
 * @param [in] file_path La localisation du fichier à lire
 * @return grid*
 *
 * @pre -
 * @post -
 *
 * Cette fonction lit ligne par ligne le fichier donné en paramètre pour charger
 * les informations sur le niveau dans la structure @c grid qu'elle alloue elle-même.
 * À part les informations sur par exemple la taille du niveau, elle charge chaque
 * case du niveau dans le tableau dynamique à deux dimension de la structure.
 * Elle recopie le niveau dans une structure et renvoi un pointeur dessus.
 */
grid *init_level(const char *file_path)
{
    // ouverture du fichier en mode lecture
    FILE *file = fopen(file_path, "r");
    // vérification si le fichier est bien ouvert
    if (!file)
    {
        fprintf(stderr, "Error %s not found", file_path);
        exit(-1);
    }
    char line[100] = {0};  // buffer pour lire une ligne dans le fichier
    int number_column = 0; // nombre de colonne
    int number_row = 0;    // nombre de ligne
    int number_goals = 0;  // nombre d'objectifs
    // on lit la première ligne du fichier
    fgets(line, 100, file);
    // on récupère les informations sur le niveau depuis la première ligne
    sscanf(line, "%d %d %d", &number_column, &number_row, &number_goals);

    // on alloue la structure pour stocker le niveau
    grid *level = creer_level(number_row, number_column, number_goals);

    int current_row = 0; // la ligne où on se trouve actuellement en lisant le niveau
    int current_goal = 0; // le nombre d'objectifs déjà réussi du niveau
    // On lit le fichier ligne par ligne jusqu'à la fin du fichier
    while (fgets(line, 100, file) != NULL)
    {
        char *buffer = line;
        int current_column = 0; // la colonne où on se trouve actuellement en lisant le niveau
        // tant qu'on arrive pas à une ligne vide ou à la fin d'une ligne, on continue à lire la ligne
        while (*buffer && *buffer != '\n')
        {
            // on charge chaque case dans la structure
            level->game_grid[current_row][current_column] = *buffer;
            // on initialise la position du joueur dans la structure quand on la retrouve
            if (*buffer == PLAYER)
            {
                level->player.x = current_column;
                level->player.y = current_row;
            } else if (*buffer == BOX_GOAL) { // on incrémente à chaque fois on trouve un objectif déjà réussi
                current_goal++;
            }

            current_column += 1;
            buffer += 1;
        }
        current_row += 1;
    }
    // on sauvegarde le nombre d'objectifs déjà réussi dans la structure de jeu
    level->box_over_goal_number = current_goal;
    // fermeture du fichier
    fclose(file);
    return level;
}

/**
 * @brief Fonction qui affiche le niveau chargé dans le terminal
 *
 * @param [in] G Pointeur sur la structure qui stocke le niveau
 *
 * @pre @a G doit être non @c NULL et pointer sur la structure allouée
 * @post Affichage des caractères
 *
 * Cette fonction parcourt le tableau dans la structure qui stocke les cases du niveau
 * et les affiche chacun. Elle utilise la fonction @c printf() de @c <stdio.h>
 */
void display(grid *G) {
    // on parcourt chaque ligne et colonne du tableau pour afficher le niveau
    for (int row = 0; row < G->row_number; row++) {
        for (int column = 0; column < G->column_number; column++) {
            printf("%c", G->game_grid[row][column]);
        }
        printf("\n");
    }
}

/**
 * @brief Fonction qui initialise la bibliothèque d'affichage @c ncurses
 *
 * @pre Il faut appeler cette fonction une fois au début du programme
 * @post Il faut appeler la fonction end_display() à la fin d'utilisation
 *
 * Cette fonction est un wrapper de la fonction d'initialisation @c ncurses
 * ainsi que d'autres options de celle-ci pour préparer l'affichage du niveau
 * de jeu avec @c ncurses
 */
void init_display()
{
    // on initialise <ncurses.h>
    initscr();
    // on efface le buffer d'avant
    clear();
    // on établi les options <ncurses.h> nécessaires
    noecho();
    cbreak();
}

/**
 * @brief Fonction qui affiche le niveau en paramètre dans le terminal avec @c ncurses
 *
 * @param [in] G Pointeur sur la structure qui stocke le niveau
 *
 * @pre @a G doit être non @c NULL et pointer sur la structure allouée
 * @pre init_display() a été appellé auparavant
 * @post Affichage à l'écran
 *
 * Cette fonction affiche le niveau du jeu comme la fonction @c display() mais au
 * contraire elle utilise la bibliothèque @c ncurses pour ne pas polluer le terminal
 * avec beaucoup d'affichages inutiles et aussi pour présenter une interface plus agréable
 * et professionnel pour le jeu.
 */
void draw_display(grid *G)
{
    // on efface le buffer d'avant
    clear();
    // on charge dans le buffer les messages sur comment interagir
    mvprintw(0, 0, "Appuyez sur \"q\" pour quitter");
    mvprintw(1, 0, "Appuyez sur \"h, j, k, l\" pour vous déplacer");
    // on recherche la taille maximale de la fenêtre
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    // on retrouve les coordonnées telles que le niveau soit centré pour commencer l'affichage
    int centerY = (maxY - G->row_number) / 2;
    int centerX = (maxX - G->column_number) / 2;
    // on parcourt chaque ligne et colonne du tableau pour charger dans le buffer
    // on veille à régler le curseur à chaque caractère pour que le niveau soit centré au final
    for (int row = 0, cursorY = centerY; row < G->row_number; row++, cursorY++)
    {
        for (int column = 0, cursorX = centerX; column < G->column_number; column++, cursorX++)
        {
            mvprintw(cursorY, cursorX, "%c", G->game_grid[row][column]);
        }
    }
    // on écarte le curseur pour ne pas être dérangé
    move(2, 0);
    // on affiche le buffer, donc le niveau entier
    refresh();
}

/**
 * @brief Fonction lit une touche au clavier avec @c ncurses et la renvoie
 *
 * @return char
 *
 * @pre init_display() a été appellé auparavant
 * @post Lecture des entrées au clavier
 *
 * Cette fonction vide complétement le buffer d'entrée du terminal avant de lire
 * une touche au clavier et la renvoyer.
 * L'utilisation de la fonction @c getch() de @c ncurses
 * est pour des raisons de cohérence mais le plus important, c'est pour lire une touche
 * sans que l'utilisateur doive appuyer sur la touche Entrée ou sans qu'il voie
 * la touche appuyée sur l'écran. Cette méthode nous permet de lire les entrées
 * directement et présenter une intéraction professionnelle. La raison pour laquelle
 * on vide le buffer avant est que pendant l'affichage d'un message d'erreur ou pendant
 * qu'on ne traite pas les entrées, l'utilisateur peut continuer à appuyer sur des touches.
 * Cela pose problème la prochaine fois on lit les entrées au clavier car on veut traiter
 * la touche la plus récente, non pas les touches qui sont restées dans le buffer pendant
 * qu'on les traitait pas. D'abord vider le buffer nous permet d'accéder à l'entrée
 * la plus récente au lieu d'attendre pour que le programme traite toutes celles qui venait
 * avant la touche la plus récente qui ne sont pas forcément utiles.
 */
char input_display()
{
    // on vide d'abord le buffer d'entrée
    nodelay(stdscr, TRUE);
    while ((getch()) != ERR);
    nodelay(stdscr, FALSE);
    // on lit une touche au clavier
    return (char)getch();
}

/**
 * @brief Fonction qui affiche un message d'erreur
 *
 * @pre init_display() a été appellé auparavant
 * @post Affichage à l'écran
 *
 * Cette fonction efface l'écran pour après afficher un message d'erreur
 * au coin à gauche en haut du terminal. Elle laisse 3 secondes à l'utilisateur
* pour lire le message affiché.
 */
void error_input_display()
{
    // on efface le buffer d'avant
    clear();
    // on charge dans le buffer un message d'erreur
    mvprintw(0, 0, "---> Cette touche n'a pas de fonctionnalité");
    // on écarte le curseur pour ne pas être dérangé
    move(1, 0);
    // on affiche le buffer, donc le message d'erreur
    refresh();
    // on donne à l'utilisateur 3 secondes pour lire le message
    napms(3000);
}

/**
 * @brief Fonction qui termine l'affichage @c ncurses
 *
 * @pre Il faut avoir appellé la fonction init_display() auparavant
 * @post Il faut appeler cette fonction une fois en fin du programme
 *
 * Cette fonction referme @c ncurses pour libérer la mémoire utilisée par
 * celle-ci.
 */
void end_display()
{
    // on referme <ncurses.h> pour désallouer la mémoire qu'elle utilisait
    endwin();
}
