#ifndef SEIR_H
#define SEIR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "utils/grid.h"

#define BETA 0.1 // Transmission rate (β)
#define GAMMA 1 // Recovery rate (γ), use 1 for discrete steps, works better with CA
#define LATENCY_PERIOD 5 // Latency period for exposed cells (σ)
#define BASE_D 10 // Base duration of infection (D), should be calculate with a random modifier for each cell

void create_seir_model(Grid *grid);
void calculate_infection_probability(Grid *grid, int x, int y);
void calculate_latency_period(const Grid *grid, int x, int y);
void can_be_exposed(Cell *cell, double *probability, int infectious_neighbors);
void can_be_infected(Cell *cell, double *probability);
void can_be_recovered(Cell *cell, double *probability);
void expose_cell(Cell *cell);
void infect_cell(Cell *cell);
void recover_cell(Cell *cell);

#endif // SEIR_H
