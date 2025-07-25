#include "cell.h"

// Assign a different state to a given cell
// Should be called when a cell suffer a state change based on probabilities
void assign_state(Cell *cell, CellState state)
{
    if (cell)
    {
        cell->value = state;
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
    return cell->value == state;
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