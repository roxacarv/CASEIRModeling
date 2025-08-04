#include "main.h"

int main(void)
{
    signal(SIGINT, sigint_handler);                       // Handle Ctrl+C to clean up resources
    srand((unsigned int)(time(NULL) ^ (uintptr_t)&main)); // Seed the random number generator with a unique value

    int moves = 0, exposures = 0, infections = 0;
    int *statistics[3] = {&moves, &exposures, &infections}; // Array to hold pointers for total moved, total infections, and total exposures

    Grid *grid = new_grid(GRID_WIDTH, GRID_HEIGHT);
    if (!grid)
    {
        return 1;
    }

    create_seir_model(grid);

    SDL_Renderer *renderer = init_sdl("SEIR Model Simulation", grid->width * CELL_SIZE + STATISTICS_WIDTH, grid->height * CELL_SIZE);
    if (!renderer)
    {
        fprintf(stderr, "Failed to initialize SDL renderer\n");
        return 1;
    }

    int time_step = 0;
    render_grid(renderer, grid); // Initial render of the grid

    TTF_Font *font = load_font();
    if (!font)
    {
        fprintf(stderr, "Failed to load font\n");
        if (renderer)
            SDL_DestroyRenderer(renderer);
        if (grid)
            free_grid(grid);
        return 1;
    }

    char *columns[] = {
        "iteration",
        "susceptible",
        "exposed",
        "infectious",
        "recovered",
        "total_moves",
        "total_exposures",
        "total_infectious",
        "avg_susceptible_count",
        "avg_exposed_count",
        "avg_infection_count",
        "avg_move_count",
        "dim"};

    create_csv(IT_CSV_FILE, columns); // Create a CSV file for logging iterations while the simulation is happening

    printf("Starting the simulation...\n");
    // Simulate the SEIR model for a number of time steps
    while (time_step <= MAX_ITERATIONS)
    {
        if (!grid)
        {
            fprintf(stderr, "Grid is NULL\n");
            break;
        }
        // clear_term(); // Clear the terminal for better visualization
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

        if ((time_step % 5) == 0)
        { // Should probably be better optimized, maybe later?
            double dim = estimate_similarity_dimension(grid, INFECTIOUS);
            save_to_csv(IT_CSV_FILE, time_step,
                        count_cells(grid, SUSCEPTIBLE),
                        count_cells(grid, EXPOSED),
                        count_cells(grid, INFECTIOUS),
                        count_cells(grid, RECOVERED),
                        *statistics[0], *statistics[1], *statistics[2],
                        calculate_avg_state_count(grid, SUSCEPTIBLE),
                        calculate_avg_state_count(grid, INFECTIOUS),
                        calculate_avg_state_count(grid, EXPOSED),
                        calculate_avg_move_count(grid), dim);
            printf("Saved current iteration to csv...\n");
        }

        track_cell_statistics(grid, statistics); // Collect statistics about the cells
        render_statistics(*statistics[0], *statistics[1], *statistics[2], time_step, renderer, font);

        // printf("Moving cell at (%d, %d) with state %d to (%d, %d)\n", x, y, cell->state, cell->x, cell->y);

        // Simulate a delay for demonstration purposes
        // sleep(1);
        time_step++;
    }
    double dim = estimate_similarity_dimension(grid, INFECTIOUS);
    // printf("Which cells caused infections:\n");
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            if (grid->cells[i][j].infection_count > 0)
            {
                // printf("Cell at (%d, %d) caused %d infections.\n", j, i, grid->cells[i][j].infection_count);
            }
        }
    }
    // printf("Which cells caused exposures:\n");
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            if (grid->cells[i][j].exposure_count > 0)
            {
                // printf("Cell at (%d, %d) caused %d exposures.\n", j, i, grid->cells[i][j].exposure_count);
            }
        }
    }
    // printf("Estimated Similarity Dimension of infection: %.3f\n", dim);
    // printf("Total Moves: %d, Total Infections: %d, Total Exposures: %d\n",
    //*statistics[0], *statistics[1], *statistics[2]);

    create_csv(CSV_FILE, columns);
    save_to_csv(CSV_FILE, time_step,
                count_cells(grid, SUSCEPTIBLE),
                count_cells(grid, EXPOSED),
                count_cells(grid, INFECTIOUS),
                count_cells(grid, RECOVERED),
                *statistics[0], *statistics[1], *statistics[2],
                calculate_avg_state_count(grid, SUSCEPTIBLE),
                calculate_avg_state_count(grid, INFECTIOUS),
                calculate_avg_state_count(grid, EXPOSED),
                calculate_avg_move_count(grid), dim);
    // Clean up SDL resources
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    free_grid(grid);
    return 0;
}

void track_cell_statistics(const Grid *grid, int *statistics[])
{
    if (!grid)
    {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }

    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            const Cell *cell = &grid->cells[i][j];
            if (!cell)
            {
                fprintf(stderr, "Cell at (%d, %d) is NULL\n", j, i);
                continue;
            }

            *statistics[0] += cell->move_count;
            *statistics[1] += cell->infection_count;
            *statistics[2] += cell->exposure_count;

            // printf("Cell at (%d, %d): State: %d, Move Count: %d, Infection Count: %d, Exposure Count: %d\n",
            // j, i, cell->state, cell->move_count, cell->infection_count, cell->exposure_count);
        }
    }
}

double calculate_avg_move_count(const Grid *grid)
{
    if (!grid)
    {
        fprintf(stderr, "Grid is NULL\n");
        return 0.0;
    }

    int total_moves = 0;
    int total_cells = 0;

    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            const Cell *cell = &grid->cells[i][j];
            if (cell)
            {
                total_moves += cell->move_count;
                total_cells++;
            }
        }
    }

    return calculate_avg(total_moves, total_cells);
}

double calculate_avg_state_count(const Grid *grid, int state)
{
    if (!grid)
    {
        fprintf(stderr, "Grid is NULL\n");
        return 0.0;
    }

    int total_count = 0;
    int total_cells = 0;

    if (state == SUSCEPTIBLE)
    {
        total_count = grid->susceptible_count;
    }
    else
    {
        for (int i = 0; i < grid->height; i++)
        {
            for (int j = 0; j < grid->width; j++)
            {
                const Cell *cell = &grid->cells[i][j];
                if (cell->state == state)
                {
                    switch (cell->state)
                    {
                    case EXPOSED:
                        total_count += cell->exposure_count;
                        break;
                    case INFECTIOUS:
                        total_count += cell->infection_count;
                        break;
                    case RECOVERED:
                        // In a SEIR model recovered cells do not contribute to infection or exposure counts
                        break;
                    }
                    total_cells++;
                }
            }
        }
    }
    if (state == EXPOSED)
    {
        printf("exposure count: %d\n", total_count);
    }
    if (state == INFECTIOUS)
    {
        printf("infectious count: %d\n", total_count);
    }
    return calculate_avg(total_count, total_cells);
}

double calculate_avg(int total, int count)
{
    return (count > 0) ? (double)total / count : 0.0;
}

void save_to_csv(char *file_path, int timestep, int S, int E, int I, int R,
                 int total_moves, int total_exposures, int total_infections,
                 double avg_susceptible_count, double avg_infection_count, double avg_exposed_count, double avg_move_count, double dim)
{
    FILE *csv_file = fopen(file_path, "a");
    if (!csv_file)
    {
        fprintf(stderr, "Failed to open CSV file for writing\n");
    }
    fprintf(csv_file,
            "%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            timestep, S, E, I, R,
            total_moves,
            total_exposures,
            total_infections,
            avg_susceptible_count,
            avg_exposed_count,
            avg_infection_count,
            avg_move_count, dim);
    fclose(csv_file);
    // printf("Statistics saved to %s\n", file_path);
}

void create_csv(char *file_path, char *columns[])
{
    char *columns_words = join_strings(columns);
    FILE *csv_file = fopen(file_path, "w");
    if (!columns_words)
    {
        fprintf(stderr, "join_strings failed\n");
        fclose(csv_file);
        return;
    }
    if (!csv_file)
    {
        fprintf(stderr, "Failed to open CSV file for writing\n");
        return;
    }
    fprintf(csv_file,
            "%s\n", columns_words);
    fclose(csv_file);
    free(columns_words);
    // printf("Statistics saved to %s\n", file_path);
}