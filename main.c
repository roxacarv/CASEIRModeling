#include "main.h"

int main(void) {
    signal(SIGINT, sigint_handler);                       // Handle Ctrl+C to clean up resources
    srand((unsigned int)(time(NULL) ^ (uintptr_t)&main)); // Seed the random number generator with a unique value

    int *statistics[3] = {0, 0, 0}; // Array to hold total moves, infections, and exposures

    for (int i = 0; i < 3; i++) {
        statistics[i] = malloc(sizeof(int));
        *statistics[i] = 0;       
    }

    Grid *grid = new_grid(32, 32);
    if (!grid) {
        return 1;
    }
    
    create_seir_model(grid);

    SDL_Renderer *renderer = init_sdl("SEIR Model Simulation", grid->width * CELL_SIZE + STATISTICS_WIDTH, grid->height * CELL_SIZE);
    if (!renderer) {
        fprintf(stderr, "Failed to initialize SDL renderer\n");
        return 1;
    }

    int time_step = 0;
    render_grid(renderer, grid); // Initial render of the grid

    TTF_Font *font = load_font();
    if (!font) {
        fprintf(stderr, "Failed to load font\n");
        return 1;
    }
    // printf("Starting the simulation...\n");
    // Simulate the SEIR model for a number of time steps
    while(time_step <= MAX_ITERATIONS) {
        if (!grid) {
            fprintf(stderr, "Grid is NULL\n");
            break;
        }
        clear_term(); // Clear the terminal for better visualization
        printf("Iteration: %d\n", time_step);
        // Randomly select a cell to move
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        Cell *cell = &grid->cells[y][x];
        
        // Print the grid after moving the cell
        // print_grid(grid);
        render_grid(renderer, grid); // Render the grid using SDL (if initialized)

        move_cell_random(grid, cell);
        calculate_infection_probability(grid, x, y);

        track_cell_statistics(grid, statistics); // Collect statistics about the cells
        render_statistics(*statistics[0], *statistics[1], *statistics[2], renderer, font);
        
        printf("Moving cell at (%d, %d) with state %d to (%d, %d)\n", x, y, cell->state, cell->x, cell->y);
        
        // Simulate a delay for demonstration purposes
        sleep(1);
        time_step++;
    }
    double dim = estimate_similarity_dimension(grid, INFECTIOUS);
    printf("Which cells caused infections:\n");
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            if (grid->cells[i][j].infection_count > 0) {
                printf("Cell at (%d, %d) caused %d infections.\n", j, i, grid->cells[i][j].infection_count);
            }
        }
    }
    printf("Which cells caused exposures:\n");
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            if (grid->cells[i][j].exposure_count > 0) {
                printf("Cell at (%d, %d) caused %d exposures.\n", j, i, grid->cells[i][j].exposure_count);
            }
        }
    }
    printf("Estimated Similarity Dimension of infection: %.3f\n", dim);
    printf("Total Moves: %d, Total Infections: %d, Total Exposures: %d\n",
           statistics[0], statistics[1], statistics[2]);
    // Clean up SDL resources
    if (renderer) {     
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    
    // Free allocated resources
    for (int i = 0; i < 3; i++) {
        free(statistics[i]);
    }
    free_grid(grid);
    return 0;
}

void track_cell_statistics(const Grid *grid, int *statistics[]) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }

    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            const Cell *cell = &grid->cells[i][j];
            if (!cell) {
                fprintf(stderr, "Cell at (%d, %d) is NULL\n", j, i);
                continue;
            }

            *statistics[0] += cell->move_count;
            *statistics[1] += cell->infection_count;
            *statistics[2] += cell->exposure_count;

            printf("Cell at (%d, %d): State: %d, Move Count: %d, Infection Count: %d, Exposure Count: %d\n",
                   j, i, cell->state, cell->move_count, cell->infection_count, cell->exposure_count);
        }
    }
}