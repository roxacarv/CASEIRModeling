#include "cell.h"

void init_cell_list(CellList *list)
{
    list->data = malloc(4 * sizeof(Cell *));
    list->size = 0;
    list->capacity = 4;
}

void append_cell(CellList *list, Cell *cell)
{
    if (list->size >= list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(Cell *));
        if (!list->data)
        {
            fprintf(stderr, "Memory allocation failed while resizing cell list\n");
            exit(EXIT_FAILURE);
        }
    }
    list->data[list->size++] = cell;
}

void free_cell_list(CellList *list)
{
    if (list)
    {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

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
    if (!cell)
    {
        fprintf(stderr, "Cell is NULL\n");
        return 0;
    }
    return cell->state == state;
}

void increase_latency_period(Cell *cell)
{
    if (cell)
    {
        cell->latency_period++;
    }
    else
    {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void increase_move_count(Cell *cell)
{
    if (cell)
    {
        cell->move_count++;
    }
    else
    {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void increase_infection_count(Cell *cell)
{
    if (cell)
    {
        cell->infection_count++;
    }
    else
    {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void increase_exposure_count(Cell *cell)
{
    if (cell)
    {
        cell->exposure_count++;
    }
    else
    {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void decrease_latency_period(Cell *cell)
{
    if (cell && cell->latency_period > 0)
    {
        cell->latency_period--;
    }
    else
    {
        fprintf(stderr, "Cell is NULL or latency period is already zero\n");
    }
}

void decrease_recovery_time(Cell *cell, int recovery_rate)
{
    if (cell && cell->recovery_time > 0)
    {
        cell->recovery_time = (cell->recovery_time > recovery_rate) ? cell->recovery_time - recovery_rate : 0;
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