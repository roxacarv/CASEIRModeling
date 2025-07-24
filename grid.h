#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>

typedef enum CellState {
    SUSCEPTIBLE = 0,
    INFECTIOUS = 1,
    EXPOSED = 2,
    RECOVERED = 3
} CellState;

typedef struct Cell {
    int x;
    int y;
    CellState value;
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
