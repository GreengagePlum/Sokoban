#include "SDL2/SDL.h"
#include "event.h"
#include "grid.h"
#include "player.h"
#include "sdl2.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
  bool sdl2 = argc > 1 && strcmp(argv[1], "sdl") != 0;
  if (sdl2)
    sdl_init();

  Event (*event_handler)() = sdl2 ? handle_sdlevent : handle_event;
  void (*display_handler)(const grid *) =
      sdl2 ? display_grid_sdl : display_grid;
  bool run = true;
  grid game_grid = init_level("level1.txt");
  display_handler(&game_grid);
  while (run) {
    switch (event_handler()) {
		case Quit:
		  run = false;
		  break;
		case Top: {
		  move_player(&game_grid, TOP);
		  break;
		}
		case Right: {
		  move_player(&game_grid, RIGHT);
		  break;
		}
		case Down: {
		  move_player(&game_grid, BOTTOM);
		  break;
		}
		case Left: {
		  move_player(&game_grid, LEFT);
		  break;
		}
		case None: break;
    }
    display_handler(&game_grid);
  }
  if (sdl2)
    sdl_quit();

  //
  //
  //
  //	grid game_grid = init_level("level1.txt");
  //	bool run = true;
  //	while(run){
  //		display_grid(game_grid);
  //		char entry = fgetc(stdin);
  //		switch(entry){
  //			case 'q' :{
  //				run = false;
  //				break;
  //			}
  //			case 'o':{
  //				move_player(&game_grid, TOP);
  //				break;
  //			}
  //			case 'm':{
  //				move_player(&game_grid, RIGHT);
  //				break;
  //			}
  //			case 'l':{
  //				move_player(&game_grid, BOTTOM);
  //				break;
  //			}
  //			case 'k':{
  //				move_player(&game_grid, LEFT);
  //				break;
  //			}
  //			case 'v':
  //				puts("Chemin du nouveau fichier");
  //				char new_level[100] = {0};
  //				free_grid(&game_grid);
  //				scanf("%s", new_level);
  //				game_grid = init_level(new_level);
  //
  //		}
  //		run = run && ! is_level_finished(&game_grid);
  //	}
  //	free_grid(&game_grid);
}
