# Compiler
CC = gcc

# Output executable
TARGET = obj/program

# Source files
SRCS = utils/grid.c utils/line.c seir.c main.c

# Build command
compile_seir:
	$(CC) $(SRCS) -o $(TARGET)

