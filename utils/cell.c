#include "cell.h"

// Assign a different state to a given cell
// Should be called when a cell suffer a state change based on probabilities
void assign_state(Cell *cell, CellState state)
{
    if (cell)
    {
        cell->state = state;
    }
    else
    {
        fprintf(stderr, "Cell is NULL\n");
    }
}

int check_cell_state(const Cell *cell, CellState state)
{
    if (!cell) {
        fprintf(stderr, "Cell is NULL\n");
        return 0;
    }
    return cell->state == state;
}

void increase_latency_period(Cell *cell)
{
    if (cell) {
        cell->latency_period++;
    } else {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void increase_move_count(Cell *cell)
{
    if (cell) {
        cell->move_count++;
    } else {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void increase_infection_count(Cell *cell)
{
    if (cell) {
        cell->infection_count++;
    } else {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void increase_exposure_count(Cell *cell)
{
    if (cell) {
        cell->exposure_count++;
    } else {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void decrease_latency_period(Cell *cell)
{
    if (cell && cell->latency_period > 0) {
        cell->latency_period--;
    } else {
        fprintf(stderr, "Cell is NULL or latency period is already zero\n");
    }
}

void decrease_recovery_time(Cell *cell)
{
    if (cell && cell->recovery_time > 0) {
        cell->recovery_time--;
    } else {
        fprintf(stderr, "Cell is NULL or recovery time is already zero\n");
    }
}

// If the cell is exposed, return if the latency period is greater than 0: the cell is still in the latency period and should not become infectious
bool is_latency_period(const Cell *cell)
{
    return cell && cell->latency_period > 0;
}

bool is_recovery_time(const Cell *cell)
{
    return cell && cell->recovery_time > 0;
}

bool is_susceptible(const Cell *cell)
{
    return check_cell_state(cell, SUSCEPTIBLE);
}

bool is_infectious(const Cell *cell)
{
    return check_cell_state(cell, INFECTIOUS);
}

bool is_exposed(const Cell *cell)
{
    return check_cell_state(cell, EXPOSED);
}

bool is_recovered(const Cell *cell)
{
    return check_cell_state(cell, RECOVERED);
}