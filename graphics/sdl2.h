#ifndef SDL_GRID_H
#define SDL_GRID_H

#include <SDL2/SDL.h>
#include <stdio.h>

#include "../utils/grid.h"
#include "../utils/cell.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 32
#define CELL_SIZE 20

SDL_Color get_color_for_state(int state);
SDL_Renderer *init_sdl(const char *title, int width, int height);
void render_grid(SDL_Renderer *ren, const Grid *grid);

#endif // SDL_GRID_H