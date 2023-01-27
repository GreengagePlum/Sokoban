/*
SDL2 interface data structures for Sokoban
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

#ifndef SDL2_H
#define SDL2_H

/**
 * @file sdl2.h
 * @author Efe ERKEN (efe.erken@etu.unistra.fr)
 * @brief Fichier header contenant la structure pour gérer @c SDL2 pour le jeu
 * @version 0.3
 * @date 2023-01-24
 *
 * @copyright Copyright (C) 2022, 2023 Efe ERKEN
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
