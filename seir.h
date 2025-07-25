#ifndef SEIR_H
#define SEIR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "utils/grid.h"

void create_seir_model(Grid *grid);
void calculate_infection_probability(const Grid *grid, int x, int y, double *probability);

#endif // SEIR_H
