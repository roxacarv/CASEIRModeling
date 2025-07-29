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

void track_cell_statistics(const Grid *grid, int *statistics[]);

#endif // MAIN_H
