// This file was generated automatically by ChatGPT
// It is a usage example for the SDL2 library in a C program
// It demonstrates how to create a simple grid and render it using SDL2

#include <SDL2/SDL.h>
#include <stdio.h>

#define GRID_WIDTH 32
#define GRID_HEIGHT 32
#define CELL_SIZE 20

enum State
{
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4
};

SDL_Color get_color_for_state(int state)
{
    switch (state)
    {
    case STATE_1:
        return (SDL_Color){0, 0, 255, 255}; // Blue
    case STATE_2:
        return (SDL_Color){255, 255, 0, 255}; // Yellow
    case STATE_3:
        return (SDL_Color){255, 0, 0, 255}; // Red
    case STATE_4:
        return (SDL_Color){0, 255, 0, 255}; // Green
    default:
        return (SDL_Color){100, 100, 100, 255}; // Gray
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("SEIR Grid",
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, 0);

    if (!win)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren)
    {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Initialize dummy grid
    int grid[GRID_HEIGHT][GRID_WIDTH];
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = rand() % 4; // Random state
        }
    }

    int running = 1;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0;
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Background black
        SDL_RenderClear(ren);

        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            for (int x = 0; x < GRID_WIDTH; x++)
            {
                SDL_Color color = get_color_for_state(grid[y][x]);
                SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
                SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1};
                SDL_RenderFillRect(ren, &rect);
            }
        }

        SDL_RenderPresent(ren);
        SDL_Delay(100); // Wait a bit (simulate frame delay)
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}