#ifndef CELL_H
#define CELL_H  

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void assign_state(Cell *cell, CellState state);
int check_cell_state(const Cell *cell, CellState state);
bool is_susceptible(const Cell *cell);
bool is_infectious(const Cell *cell);
bool is_exposed(const Cell *cell);
bool is_recovered(const Cell *cell);

#endif // CELL_H