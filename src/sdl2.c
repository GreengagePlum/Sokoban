/*
SDL2 display management functions for Sokoban
Copyright (C) 2022, 2023 Efe ERKEN

This file is part of Sokoban

Sokoban is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sokoban is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sokoban.  If not, see <https://www.gnu.org/licenses/>.

SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file sdl2.c
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier source contenant les fonctions et autres pour gérer @c SDL2 pour le jeu
 * @version 0.3
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
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
