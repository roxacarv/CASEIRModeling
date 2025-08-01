#include "line.h"

void cleanup() {
    printf("Cleaning up resources...\n");
}

void sigint_handler(int sig) {
    cleanup();
    exit(0);
}

void clear_term() {
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}

void clear_term_posix() {
    // Clear the terminal screen
    printf("\e[1;1H\e[2J");
}


char *join_strings(char *arr[]) {
    int total_len = 0;
    int count = 0;
    for (int i = 0; arr[i] != NULL; i++) {
        total_len += strlen(arr[i]);
        count++;
    }
    total_len += count - 1;

    // Allocate memory (+1 for '\0')
    char *result = malloc(total_len + 1);
    if (!result) return NULL;

    result[0] = '\0';

    for (int i = 0; i < count; i++) {
        strcat(result, arr[i]);
        if (i < count - 1) {
            strcat(result, ",");
        }
    }

    return result;
}