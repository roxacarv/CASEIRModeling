#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#include "utils/grid.h"
#include "utils/line.h"
#include "utils/dim.h"
#include "graphics/sdl2.h"
#include "seir.h"

#define MAX_ITERATIONS 150
#define CELL_SIZE 20
#define CSV_FILE "statistics.csv"

void track_cell_statistics(const Grid *grid, int *statistics[]);
double calculate_avg_move_count(const Grid *grid);
double calculate_avg_state_count(const Grid *grid, int state);
double calculate_avg(const int total, const int count);
void save_to_csv(FILE *csv_file, int timestep, int S, int E, int I, int R,
                  int total_moves, int total_exposures, int total_infections,
                  double avg_infection_count, double avg_exposed_count, double avg_move_count);

#endif // MAIN_H
