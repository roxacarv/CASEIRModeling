#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void cleanup();
void sigint_handler(int sig);
void clear_term();
void clear_term_posix();
char *join_strings(char *arr[]);

#endif // LINE_H