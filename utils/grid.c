#include "grid.h"

Grid *new_grid(int width, int height) {
    Grid *grid = malloc(sizeof(Grid));
    if (!grid) {
        fprintf(stderr, "Memory allocation failed for grid\n");
        return NULL;
    } 
    grid->width = width;
    grid->height = height;
    grid->cells = malloc(height * sizeof(Cell *));
    if (!grid->cells) {
        fprintf(stderr, "Memory allocation failed for grid cells\n");
        free(grid);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        grid->cells[i] = malloc(width * sizeof(Cell));
        if (!grid->cells[i]) {
            fprintf(stderr, "Memory allocation failed for row %d of grid cells\n", i);
            for (int j = 0; j < i; j++) {
                free(grid->cells[j]);
            }
            free(grid->cells);
            free(grid);
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            grid->cells[i][j].x = j;
            grid->cells[i][j].y = i;
            grid->cells[i][j].value = SUSCEPTIBLE; // Initialize to susceptible state
            grid->cells[i][j].next = NULL;
        }
    }
    return grid;
}

void update_cell(Grid *grid, int x, int y, int new_value) {
    if (!grid || x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        fprintf(stderr, "Invalid grid or coordinates\n");
        return;
    }
    grid->cells[y][x].value = new_value;
}

void free_grid(Grid *grid) {
    if (grid) {
        for (int i = 0; i < grid->height; i++) {
            free(grid->cells[i]);
        }
        free(grid->cells);
        free(grid);
    }
}

void print_grid(const Grid *grid) {
    if (!grid) {
        printf("Grid is NULL\n");
        return;
    }
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            printf("%d ", grid->cells[i][j].value);
        }
        printf("\n");
    }
}

// Moves a cell through the grid, to simulate its movement as if it were a person
void move_cell(Grid *grid, Cell *cell, int new_x, int new_y)
{
    if (!grid || !cell)
    {
        fprintf(stderr, "Grid or cell is NULL\n");
        return;
    }

    if (new_x < 0 || new_x >= grid->width || new_y < 0 || new_y >= grid->height)
    {
        fprintf(stderr, "New position out of bounds\n");
        return;
    }

    cell->x = new_x;
    cell->y = new_y;
    grid->cells[new_y][new_x] = *cell; // Update the grid with the new cell position
}

// Moves a cell through the grid, to simulate its movement as if it were a person
void move_cell_random(Grid *grid, Cell *cell)
{
    if (!grid || !cell)
    {
        fprintf(stderr, "Grid or cell is NULL\n");
        return;
    }

    int new_x = rand() % grid->width;
    int new_y = rand() % grid->height;

    move_cell(grid, cell, new_x, new_y);
}
