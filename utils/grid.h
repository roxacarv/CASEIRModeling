#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

typedef struct Grid {
    Cell **cells;
    int width;
    int height;
} Grid;

Grid *new_grid(int width, int height);
void free_grid(Grid *grid);
void update_cell(Grid *grid, int x, int y, int new_value);
void print_grid(const Grid *grid);
void move_cell(Grid *grid, Cell *cell, int new_x, int new_y);
void move_cell_random(Grid *grid, Cell *cell);

#endif // GRID_H
