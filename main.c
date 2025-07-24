#include "main.h"

int main(void) {
    Grid *grid = new_grid(10, 10);
    if (!grid) {
        return 1;
    }
    print_grid(grid);
    update_cell(grid, 5, 5, INFECTED);
    print_grid(grid);
    free_grid(grid);
    return 0;
}