#ifndef SEIR_H
#define SEIR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils/grid.h"

void create_seir_model(Grid *grid);
void assign_state(Cell *cell, CellState state);
void get_cell_state(const Cell *cell, CellState *state);
void move_cell(Grid *grid, Cell *cell, int new_x, int new_y);
void move_cell_random(Grid *grid, Cell *cell);

#endif // SEIR_H
