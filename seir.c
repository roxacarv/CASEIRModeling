#include "seir.h"

// Create a SEIR model on the grid, by defining the initial states of the cells
// It randomly assigns states such as (I) and (E) to some cells
// Other cells will remain susceptible (S)
void create_seir_model(Grid *grid) {
    srand(time(NULL)); // Seed the random number generator
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    
    // Decide randomly the initial state of each cell
    // For simplicity, all cells are initialized to susceptible state
    // Randomly sort the number of cells to be infected or exposed
    int infectious_cells = grid->width * grid->height / 10; // 10% of cells infected
    int exposed_cells = grid->width * grid->height / 20; // 5% of cells exposed

    // Randomly select cells to be infected or exposed
    for (int i = 0; i < infectious_cells; i++) {
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        grid->cells[y][x].value = INFECTIOUS;
    }

    for (int i = 0; i < exposed_cells; i++) {
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        grid->cells[y][x].value = EXPOSED;
    }

    printf("SEIR model initialized on the grid.\n");
    printf("Grid dimensions: %d x %d\n", grid->width, grid->height);
    printf("Infectious cells: %d, Exposed cells: %d\n", infectious_cells, exposed_cells);
    print_grid(grid);
}

// Assign a different state to a given cell
// Should be called when a cell suffer a state change based on probabilities
void assign_state(Cell *cell, CellState state) {
    if (cell) {
        cell->value = state;
    } else {
        fprintf(stderr, "Cell is NULL\n");
    }
}

void get_cell_state(const Cell *cell, CellState *state) {
    if (cell && state) {
        *state = cell->value;
    } else {
        fprintf(stderr, "Cell or state pointer is NULL\n");
    }
}

// Moves a cell through the grid, to simulate its movement as if it were a person
void move_cell(Grid *grid, Cell *cell, int new_x, int new_y) {
    if (!grid || !cell) {
        fprintf(stderr, "Grid or cell is NULL\n");
        return;
    }
    
    if (new_x < 0 || new_x >= grid->width || new_y < 0 || new_y >= grid->height) {
        fprintf(stderr, "New position out of bounds\n");
        return;
    }

    cell->x = new_x;
    cell->y = new_y;
}