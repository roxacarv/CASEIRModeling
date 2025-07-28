#ifndef SEIR_H
#define SEIR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "utils/grid.h"

#define BETA 0.1 // Transmission rate (β)
#define GAMMA 0.2 // Recovery rate (γ)
#define LATENCY_PERIOD 5 // Latency period for exposed cells (σ)

void create_seir_model(Grid *grid);
void calculate_infection_probability(Grid *grid, int x, int y);
void expose_cell(Grid *grid, int x, int y);
void infect_cell(Grid *grid, int x, int y);
void recover_cell(Grid *grid, int x, int y);

#endif // SEIR_H
