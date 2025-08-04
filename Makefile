# Compiler
CC = gcc
DB = gdb

# Output executable
TARGET = obj/program

# Source files
SRCS = utils/cell.c utils/grid.c graphics/sdl2.c utils/dim.c utils/line.c seir.c main.c

# Debug command
gdb:
	$(CC) -g $(SRCS) -o $(TARGET) -lm `sdl2-config --cflags --libs` -lSDL2_ttf

# Build command
build:
	$(CC) $(SRCS) -o $(TARGET) -lm `sdl2-config --cflags --libs` -lSDL2_ttf
