#ifndef SDL_GRID_H
#define SDL_GRID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "../utils/grid.h"
#include "../utils/cell.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 32
#define CELL_SIZE 20
#define FONT_PATH "graphics/fonts/OpenSans-VariableFont.ttf"
#define FONT_SIZE 16
#define STATISTICS_WIDTH 200

SDL_Color get_color_for_state(int state);
SDL_Renderer *init_sdl(const char *title, int width, int height);
void render_grid(SDL_Renderer *ren, const Grid *grid);
void render_statistics(int total_moved, int total_infections, int total_exposures, SDL_Renderer *renderer, TTF_Font *font);
void render_text_line(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color);
TTF_Font *load_font();

#endif // SDL_GRID_H