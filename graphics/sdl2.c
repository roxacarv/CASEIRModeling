#include "sdl2.h"

SDL_Color get_color_for_state(int state) {
    switch (state) {
        case SUSCEPTIBLE: return (SDL_Color){0, 0, 255, 255};     // Blue
        case EXPOSED:     return (SDL_Color){255, 255, 0, 255};   // Yellow
        case INFECTIOUS:  return (SDL_Color){255, 0, 0, 255};     // Red
        case RECOVERED:   return (SDL_Color){0, 255, 0, 255};     // Green
        default:          return (SDL_Color){100, 100, 100, 255}; // Gray
    }
}

SDL_Renderer *init_sdl(const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    return renderer;
}

void render_grid(SDL_Renderer *ren, const Grid *grid) {
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            SDL_Color color = get_color_for_state(grid->cells[y][x].state);
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_Rect cell_rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(ren, &cell_rect);
        }
    }
    SDL_RenderPresent(ren);
}