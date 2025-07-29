#ifndef DIM_H
#define DIM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "grid.h"

double estimate_similarity_dimension(const Grid *grid, CellState target_state);
double calculate_similarity_dim(int sizes[], int *counts, int num_sizes);

#endif // DIM_H
