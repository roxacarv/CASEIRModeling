#include "sdl2.h"

SDL_Color get_color_for_state(int state)
{
    switch (state)
    {
    case SUSCEPTIBLE:
        return (SDL_Color){0, 0, 255, 255}; // Blue
    case EXPOSED:
        return (SDL_Color){255, 255, 0, 255}; // Yellow
    case INFECTIOUS:
        return (SDL_Color){255, 0, 0, 255}; // Red
    case RECOVERED:
        return (SDL_Color){0, 255, 0, 255}; // Green
    default:
        return (SDL_Color){100, 100, 100, 255}; // Gray
    }
}

SDL_Renderer *init_sdl(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    return renderer;
}

void render_grid(SDL_Renderer *ren, const Grid *grid)
{
    for (int y = 0; y < grid->height; y++)
    {
        for (int x = 0; x < grid->width; x++)
        {
            SDL_Color color = get_color_for_state(grid->cells[y][x].state);
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_Rect cell_rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(ren, &cell_rect);
        }
    }
    SDL_RenderPresent(ren);
}

void render_statistics(int total_moved, int total_infections, int total_exposures, int iteration, SDL_Renderer *renderer, TTF_Font *font) {
    if (!renderer || !font) return;
    
    SDL_Color white = {255, 255, 255, 255};
    char buffer[128];
    int y_offset = 10;
    int x = GRID_WIDTH * CELL_SIZE + 10;

    sprintf(buffer, "Iteration: %d", iteration);
    render_text_line(renderer, font, buffer, x, y_offset, white);
    y_offset += 25;

    sprintf(buffer, "Total Grid Moves: %d", total_moved);
    render_text_line(renderer, font, buffer, x, y_offset, white);
    y_offset += 25;

    sprintf(buffer, "Total Infections: %d", total_infections);
    render_text_line(renderer, font, buffer, x, y_offset, white);
    y_offset += 25;

    sprintf(buffer, "Total Exposures: %d", total_exposures);
    render_text_line(renderer, font, buffer, x, y_offset, white);
}

void render_text_line(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dest = { x, y, surface->w, surface->h };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &dest);

    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

TTF_Font *load_font()
{
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        return NULL;
    }

    TTF_Font *font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font)
    {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    }
    else
    {
        printf("Font loaded successfully.\n");
    }
    return font;
}