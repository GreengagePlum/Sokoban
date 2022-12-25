#ifndef SDL2_H
#define SDL2_H

/**
 * @file sdl2.h
 * @brief Fichier header contenant la structure pour gérer @c SDL2 pour le jeu
 * @version 0.2
 * @date 2022-12-25
 *
 */

#include <SDL2/SDL.h>

/**
 * @brief Structure contenant les informations pour l'affichage @c SDL2
 *
 * Cette structure contient les informations telles que la fenêtre, le renderer,
 * la taille de la fenêtre @c SDL2 pour faciliter l'utilisation de cette bibliothèque
 * dans le jeu.
 */
typedef struct SDLContext
{
    SDL_Window *window;     ///< Pointeur sur la fenêtre
    SDL_Renderer *renderer; ///< Pointeur sur le renderer
    int width;              ///< Largeur de la fenêtre
    int height;             ///< Hauteur de la fenêtre
} SDLContext;

extern SDLContext context;

void sdl_init();

void sdl_quit();

#endif
