#include "main.h"
#include "seir.h"

int main(void) {
    Grid *grid = new_grid(10, 10);
    if (!grid) {
        return 1;
    }
    create_seir_model(grid);
    print_grid(grid);
    free_grid(grid);
    printf("Simulation completed successfully.\n");
    return 0;
}