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
    int latency_period; // For exposed cells, to track the latency period
    int recovery_time;  // For infectious cells, to track the recovery time
    int move_count;     // To track the number of moves made by the cell
    int infection_count; // To track the number of infections caused by the cell
    int exposure_count;  // To track the number of exposures caused by the cell
    CellState state;
    struct Cell *next;
} Cell;

void assign_state(Cell *cell, CellState state);
int check_cell_state(const Cell *cell, CellState state);
void increase_latency_period(Cell *cell);
void increase_move_count(Cell *cell);
void increase_infection_count(Cell *cell);
void increase_exposure_count(Cell *cell);
void decrease_latency_period(Cell *cell);
void decrease_recovery_time(Cell *cell);
bool is_latency_period(const Cell *cell);
bool is_recovery_time(const Cell *cell);
bool is_susceptible(const Cell *cell);
bool is_infectious(const Cell *cell);
bool is_exposed(const Cell *cell);
bool is_recovered(const Cell *cell);

#endif // CELL_H