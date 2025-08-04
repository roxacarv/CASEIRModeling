#include "line.h"

void cleanup()
{
    printf("Cleaning up resources...\n");
}

void sigint_handler(int sig)
{
    cleanup();
    exit(0);
}

void clear_term()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}

void clear_term_posix()
{
    // Clear the terminal screen
    printf("\e[1;1H\e[2J");
}

char *join_strings(char *arr[]) {
    if (!arr) return NULL;

    int total_len = 0;
    int count = 0;
    for (int i = 0; arr[i] != NULL; i++) {
        total_len += strlen(arr[i]);
        count++;
    }
    if (count > 1) {
        total_len += count - 1;  // commas
    }

    char *result = malloc(total_len + 1);
    if (!result) return NULL;

    char *p = result;
    for (int i = 0; i < count; i++) {
        size_t len = strlen(arr[i]);
        memcpy(p, arr[i], len);
        p += len;

        if (i < count - 1) {
            *p = ',';
            p++;
        }
    }
    *p = '\0';

    return result;
}