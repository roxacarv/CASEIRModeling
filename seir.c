#include "seir.h"

// Create a SEIR model on the grid, by defining the initial states of the cells
// It randomly assigns states such as (I) and (E) to some cells
// Other cells will remain susceptible (S)
void create_seir_model(Grid *grid)
{
    srand(time(NULL)); // Seed the random number generator
    if (!grid)
    {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }

    // Decide randomly the initial state of each cell
    // For simplicity, all cells are initialized to susceptible state
    // Randomly sort the number of cells to be infected or exposed
    int infectious_cells = grid->width * grid->height / 10; // 10% of cells infected
    int exposed_cells = grid->width * grid->height / 20;    // 5% of cells exposed

    // Randomly select cells to be infected or exposed
    for (int i = 0; i < infectious_cells; i++)
    {
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        grid->cells[y][x].state = INFECTIOUS;
    }

    for (int i = 0; i < exposed_cells; i++)
    {
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        grid->cells[y][x].state = EXPOSED;
    }

    printf("SEIR model initialized on the grid.\n");
    printf("Grid dimensions: %d x %d\n", grid->width, grid->height);
    printf("Infectious cells: %d, Exposed cells: %d\n", infectious_cells, exposed_cells);
    print_grid(grid);
}

/**
 * Area with functions related to the model equations for probabilities
 * These functions will be used to calculate the probabilities of state changes, including infection, exposure, and recovery.
 * Legend:
 *      (MID) - Microparasitic Infectious Diseases
 *      (S)   - Susceptible
 *      (E)   - Exposed
 *      (I)   - Infectious
 *      (R)   - Recovered
 *      (γ)   - Recover probability
 *      (D)   - Duration of infection
 *      (β)   - Transmission rate
 *      (σ)   - Latency period of infection
 */

// Calculate the infection probability for a cell based on its neighbors
// The algorithm used is Moore's neighborhood
// It counts the number of infectious neighbors and calculates the probability of infection
// P(infection) = 1 - (1 - β) ^ n, where n = number of (I) neighbors
// This function will be used to determine if a susceptible cell
// will become exposed or infectious based on the infection probability
void calculate_infection_probability(Grid *grid, int x, int y)
{
    double *probability = malloc(sizeof(double));
    if (!probability)
    {
        fprintf(stderr, "Memory allocation failed for probability\n");
        return;
    }
    *probability = 0.0; // Initialize the probability to 0

    if (!grid || x < 0 || x >= grid->width || y < 0 || y >= grid->height)
    {
        fprintf(stderr, "Invalid grid or coordinates\n");
        return;
    }

    int width = grid->width;
    int height = grid->height;
    int infectious_neighbors = 0;

    // Define the Moore neighborhood offsets
    int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    // Count infectious neighbors
    for (int i = 0; i < 8; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) // This will check if the new position is within the grid bounds before proceeding to check the cell state
        {
            if (check_cell_state(&grid->cells[new_y][new_x], INFECTIOUS))
            {
                infectious_neighbors++;
            }
        }
    }

    printf("Number of infectious neighbors for cell at (%d, %d): %d\n", x, y, infectious_neighbors);

    if (infectious_neighbors == 0)
    {
        *probability = 0.0; // No infectious neighbors, no infection probability
        return;
    }

    // Calculate the infection probability
    if (is_susceptible(&grid->cells[y][x]))
    {
        can_be_exposed(&grid->cells[y][x], probability, infectious_neighbors); // Check if the cell can be exposed
    }

    if (is_exposed(&grid->cells[y][x]))
    {
        can_be_infected(&grid->cells[y][x], probability);
    }

    if (is_infectious(&grid->cells[y][x]))
    {
        can_be_recovered(&grid->cells[y][x], probability);
    }

    if (is_recovered(&grid->cells[y][x]))
    {
        // If the cell is recovered, it remains in the recovered state
        *probability = 0.0;
    }

    printf("Infection probability for cell at (%d, %d): %.2f\n", x, y, *probability);
}

void calculate_latency_period(const Grid *grid, int x, int y)
{
    if (!grid || x < 0 || x >= grid->width || y < 0 || y >= grid->height)
    {
        fprintf(stderr, "Invalid grid or coordinates\n");
        return;
    }

    //
    Cell *cell = &grid->cells[y][x];
    if (is_exposed(cell))
    {
        printf("Cell at (%d, %d) is exposed with a latency period of %d time steps.\n", x, y, cell->latency_period);
    }
}

void can_be_exposed(Cell *cell, double *probability, int infectious_neighbors)
{
    // If the cell is susceptible, calculate the infection probability based on infectious neighbors
    double rand_value = (double)(rand() / RAND_MAX); // Generate a random number between 0 and 1, this number will be used to determine if the cell will become exposed or infectious
    *probability = 1.0 - pow((1.0 - BETA), infectious_neighbors);
    if (rand_value < *probability)
    {
        // If the random value is less than the calculated probability, the cell becomes exposed
        expose_cell(cell);
    }
}

void can_be_infected(Cell *cell, double *probability)
{
    if (is_latency_period(cell))
    {
        // If the cell is exposed and in the latency period, it will not become infectious yet
        // We assume the MID (Microparasitic Infectious Diseases) pathogen has a latency period
        *probability = 0.0;
        decrease_latency_period(cell); // Decrease the latency period for the exposed cell
    }
    else
    {
        infect_cell(cell);
    }
}

void can_be_recovered(Cell *cell, double *probability)
{
    if (is_recovery_time(cell))
    {
        *probability = 0.0;
        recover_cell(cell);
    }
    decrease_recovery_time(cell);
}

void expose_cell(Cell *cell)
{
    if (!cell)
    {
        fprintf(stderr, "Invalid grid or coordinates\n");
        return;
    }

    assign_state(cell, EXPOSED);
    printf("Cell at (%d, %d) has been exposed.\n", cell->x, cell->y);
}

void infect_cell(Cell *cell)
{
    if (!cell)
    {
        fprintf(stderr, "Invalid cell\n");
        return;
    }

    assign_state(cell, INFECTIOUS);
    printf("Cell at (%d, %d) has been infected.\n", cell->x, cell->y);
}

void recover_cell(Cell *cell)
{
    if (!cell)
    {
        fprintf(stderr, "Invalid cell\n");
        return;
    }

    assign_state(cell, RECOVERED);
    printf("Cell at (%d, %d) has recovered.\n", cell->x, cell->y);
}