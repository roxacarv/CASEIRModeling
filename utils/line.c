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