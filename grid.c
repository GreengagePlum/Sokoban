/**
 * @file grid.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source contenant les fonctions pour traiter les niveaux du jeu sokoban
 * @version 0.1
 * @date 2022-11-10
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
 * Cette fonction prend en paramètre deux arguments tels que le nombre de lignes
 * et le nombre de colonnes du niveau de jeu. Elle alloue dynamiquement la structure @c grid
 * en fonction de cette taille et renvoie un pointeur sur cette structure.
 */
grid *creer_level(int row, int column)
{
    // on alloue la structure elle-même dynamiquement
    grid *G = (grid *)malloc(sizeof(grid));
    // on vérifie si l'allocation s'est bien passée
    if (G == NULL)
    {
        fprintf(stderr, "Error G structure alloc failed");
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
    // on initialise les valeurs de taille du niveau
    G->row_number = row;
    G->column_number = column;
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
    char line[100] = {0}; // buffer pour lire une ligne dans le fichier
    int number_column = 0; // nombre de colonne
    int number_row = 0; // nombre de ligne
    int number_goals = 0; // nombre d'objectifs
    // on lit la première ligne du fichier
    fgets(line, 100, file);
    // on récupère les informations sur le niveau depuis la première ligne
    sscanf(line, "%d %d %d", &number_column, &number_row, &number_goals);

    // on alloue la structure pour stocker le niveau
    grid *level = creer_level(number_row, number_column);

    int current_row = 0; // la ligne où on se trouve actuellement en lisant le niveau
    // int current_goal = 0;
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
 * @brief Fonction qui affiche le niveau chargé dans le terminal avec @c ncurses
 *
 * @param [in] G Pointeur sur la structure qui stocke le niveau
 *
 * @pre @a G doit être non @c NULL et pointer sur la structure allouée
 * @post Affichage des caractères, appuyez sur 'q' pour quitter
 *
 * Cette fonction affiche le niveau du jeu comme la fonction @c display() mais au
 * contraire elle utilise la bibliothèque @c <ncurses.h> pour ne pas polluer le terminal
 * avec beaucoup d'affichages inutiles et aussi pour présenter une interface plus agréable
 * et professionnel pour le jeu.
 */
void display_ncurses(grid *G) {
    // on initialise <ncurses.h>
    initscr();
    // on efface le buffer d'avant
    clear();
    noecho();
    cbreak();
    printw("Appuyez sur \"q\" pour quitter\n");
    // on parcourt chaque ligne et colonne du tableau pour charger dans le buffer
    for (int row = 0; row < G->row_number; row++) {
        for (int column = 0; column < G->column_number; column++) {
            printw("%c", G->game_grid[row][column]);
        }
        printw("\n");
    }
    // on affiche le buffer, donc le niveau entier
    refresh();
    // on attend jusqu'à ce que l'utilisateur appuie sur la touche 'q' pour quitter
    char quitCar = '\0';
    while (quitCar != 'q') {
        quitCar = (char) getch();
    }
    // on referme <ncurses.h> pour désallouer la mémoire qu'elle utilisait
    endwin();
}
