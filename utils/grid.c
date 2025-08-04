#include "grid.h"

Grid *new_grid(int width, int height) {
    Grid *grid = malloc(sizeof(Grid));
    if (!grid) {
        fprintf(stderr, "Memory allocation failed for grid\n");
        return NULL;
    } 
    grid->width = width;
    grid->height = height;
    grid->cells = malloc(height * sizeof(Cell *));
    if (!grid->cells) {
        fprintf(stderr, "Memory allocation failed for grid cells\n");
        free(grid);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        grid->cells[i] = malloc(width * sizeof(Cell));
        if (!grid->cells[i]) {
            fprintf(stderr, "Memory allocation failed for row %d of grid cells\n", i);
            for (int j = 0; j < i; j++) {
                free(grid->cells[j]);
            }
            free(grid->cells);
            free(grid);
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            grid->cells[i][j].x = j;
            grid->cells[i][j].y = i;
            grid->cells[i][j].state = SUSCEPTIBLE; // Initialize to susceptible state
            grid->cells[i][j].next = NULL;
        }
    }
    return grid;
}

void update_cell(Grid *grid, int x, int y, int new_value) {
    if (!grid || x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        fprintf(stderr, "Invalid grid or coordinates\n");
        return;
    }
    grid->cells[y][x].state = new_value;
}

void free_grid(Grid *grid) {
    if (grid) {
        for (int i = 0; i < grid->height; i++) {
            free(grid->cells[i]);
        }
        free(grid->cells);
        free(grid);
    }
}

void print_grid(const Grid *grid) {
    if (!grid) {
        printf("Grid is NULL\n");
        return;
    }
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            printf("%d ", grid->cells[i][j].state);
        }
        printf("\n");
    }
}

// Moves a cell through the grid, to simulate its movement as if it were a person
// Instead of only moving, add a swap to avoid letting old cells hanging
void move_cell(Grid *grid, Cell *cell, int new_x, int new_y)
{
    if (!grid || !cell)
    {
        fprintf(stderr, "Grid or cell is NULL\n");
        return;
    }

    if (new_x < 0 || new_x >= grid->width || new_y < 0 || new_y >= grid->height)
    {
        fprintf(stderr, "New position out of bounds\n");
        return;
    }

    int old_x = cell->x;
    int old_y = cell->y;

    if (old_x == new_x && old_y == new_y) {
        return;
    }

    // Pointer to the target cell to swap with
    Cell *target_cell = &grid->cells[new_y][new_x];

    // Swap the cells in the grid array
    Cell temp = *cell;
    *cell = *target_cell;
    *target_cell = temp;

    cell->x = old_x;
    cell->y = old_y;

    target_cell->x = new_x;
    target_cell->y = new_y;

    // Increment move count for the moved cell (which is now at target position)
    target_cell->move_count++;
}

// Moves a cell through the grid, to simulate its movement as if it were a person
void move_cell_random(Grid *grid, Cell *cell)
{
    if (!grid || !cell)
    {
        fprintf(stderr, "Grid or cell is NULL\n");
        return;
    }

    int new_x = rand() % grid->width;
    int new_y = rand() % grid->height;

    move_cell(grid, cell, new_x, new_y);
}

int count_cells(const Grid *grid, CellState state) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return 0;
    }
    int count = 0;
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            if (grid->cells[i][j].state == state) {
                count++;
            }
        }
    }
    return count;
}