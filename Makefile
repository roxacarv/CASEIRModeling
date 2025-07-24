# Compiler
CC = gcc

# Output executable
TARGET = program

# Source files
SRCS = utils/grid.c seir.c main.c

# Build command
compile_seir:
	$(CC) $(SRCS) -o $(TARGET)

