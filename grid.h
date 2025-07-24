#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define SUSCEPTIBLE 0
#define INFECTED 1
#define EXPOSED 2
#define RECOVERED 3

typedef struct Cell {
    int x;
    int y;
    int value;
    struct Cell *next;
} Cell;

typedef struct Grid {
    Cell **cells;
    int width;
    int height;
} Grid;

Grid *new_grid(int width, int height);
void free_grid(Grid *grid);
void update_cell(Grid *grid, int x, int y, int new_value);
void print_grid(const Grid *grid);

#endif // GRID_H