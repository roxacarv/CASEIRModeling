#ifndef DIM_H
#define DIM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "grid.h"

double estimate_similarity_dimension(const Grid *grid, CellState target_state);

#endif // DIM_H
