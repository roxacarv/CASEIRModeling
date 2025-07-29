# Compiler
CC = gcc

# Output executable
TARGET = obj/program

# Source files
SRCS = utils/cell.c utils/grid.c graphics/sdl2.c utils/dim.c utils/line.c seir.c main.c

# Build command
compile:
	$(CC) $(SRCS) -o $(TARGET) -lm -lSDL2

