#include "dim.h"

double estimate_similarity_dimension(const Grid *grid, CellState target_state) {
    int sizes[] = {1, 2, 4, 8, 16, 32}; // box sizes (you can expand this)
    int counts[sizeof(sizes)/sizeof(sizes[0])];
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int box_size = sizes[s];
        int count = 0;

        for (int i = 0; i < grid->height; i += box_size) {
            for (int j = 0; j < grid->width; j += box_size) {
                bool found = false;

                for (int y = i; y < i + box_size && y < grid->height && !found; y++) {
                    for (int x = j; x < j + box_size && x < grid->width; x++) {
                        if (grid->cells[y][x].state == target_state) {
                            found = true;
                            break;
                        }
                    }
                }

                if (found) count++;
            }
        }

        counts[s] = count;
    }

    // Using linear regression: log(counts) vs log(1 / box_size)
    double sum_log_r = 0;
    double sum_log_n = 0;
    double sum_log_rn = 0;
    double sum_log_r2 = 0;

    // Calculate sums for linear regression
    for (int i = 0; i < num_sizes; i++) { // Ignore empty boxes
        if (sizes[i] <= 0) continue; // Avoid division by zero
        if (counts[i] == 0) continue;
        double r = 1.0 / sizes[i];
        double log_r = log(r);
        double log_n = log(counts[i]);

        sum_log_r += log_r;
        sum_log_n += log_n;
        sum_log_rn += log_r * log_n;
        sum_log_r2 += log_r * log_r;
    }

    double n = num_sizes;
    double numerator = n * sum_log_rn - sum_log_r * sum_log_n;
    double denominator = n * sum_log_r2 - sum_log_r * sum_log_r;

    if (denominator == 0) return 0;

    double similarity_dimension = numerator / denominator;

    return similarity_dimension;
}
