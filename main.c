#include "main.h"

int main(void) {
    signal(SIGINT, sigint_handler); // Handle Ctrl+C to clean up resources

    Grid *grid = new_grid(15, 15);
    if (!grid) {
        return 1;
    }

    create_seir_model(grid);
    print_grid(grid);

    int time_step = 0;

    printf("Starting the simulation...\n");
    // Simulate the SEIR model for a number of time steps
    while(time_step <= MAX_ITERATIONS) {
        if (!grid) {
            fprintf(stderr, "Grid is NULL\n");
            break;
        }
        clear_term(); // Clear the terminal for better visualization
        printf("Iteration: %d\n", time_step);
        srand(time(NULL) + time_step); // Seed the random number generator with time step for variability
        // Randomly select a cell to move
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        Cell *cell = &grid->cells[y][x];
        move_cell_random(grid, cell);
        printf("Moving cell at (%d, %d) with state %d to (%d, %d)\n", x, y, cell->value, cell->x, cell->y);

        // Print the grid after moving the cell
        print_grid(grid);
        
        // Simulate a delay for demonstration purposes
        sleep(1);
        time_step++;
    }

    free_grid(grid);
    return 0;
}
