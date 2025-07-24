#include "seir.h"

void create_seir_model(Grid *grid) {
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
        grid->cells[y][x].value = INFECTED;
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