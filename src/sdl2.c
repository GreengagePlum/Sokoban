/**
 * @file sdl2.c
 * @brief Fichier source contenant les fonctions et autres pour gérer @c SDL2 pour le jeu
 * @version 0.2
 * @date 2022-12-25
 *
 */

#include "sdl2.h"

SDLContext context;

/**
 * @brief Fonction qui lance @c SDL2 et crée une fenêtre
 *
 * @pre -
 * @post Création d'une nouvelle fenêtre
 *
 * Initialise une variable global `context` de type SDLContext.
 * Si il y a erreur pendant l'intialisation: context.window = NULL ou context.renderer = NULL.
 * Les deux cas sont à tester !
 */
void sdl_init()
{
    // la taille de la fenêtre
    int const width = 1280;
    int const height = 720;
    // initialisation à zero du context
    context = (SDLContext){NULL, NULL, .width = 0, .height = 0};
    // lancement du système video et événement de SDL2
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        return;
    }
    // création d'une fenêtre
    SDL_Window *window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        return;
    }
    // création d'un renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // mise à jour du context avec les nouvelles informations
    context = (SDLContext){.window = window, .renderer = renderer, .width = width, .height = height};
}

/**
 * @brief Fonction qui referme la bibliothèque @c SDL2
 *
 * @pre Avoir appelé la fonction @c sdl_init() auparavant
 * @post -
 *
 * Cette fonction détruit la fenêtre et le renderer utilisé,
 * elle nettoie la variable global context et finalement elle referme la @c SDL2
 * pour libérer la mémoire utilisé par celle-ci.
 */
void sdl_quit()
{
    SDL_DestroyWindow(context.window);
    SDL_DestroyRenderer(context.renderer);
    context.window = NULL;
    context.renderer = NULL;
    SDL_Quit();
}
