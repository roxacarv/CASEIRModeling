# Compiler and debugger
CC  = gcc
DB  = gdb

# Output executable
TARGET = obj/program

# Source files
SRCS = utils/cell.c utils/grid.c graphics/sdl2.c utils/dim.c utils/line.c seir.c main.c

# Compiler flags
CFLAGS  = `sdl2-config --cflags`
LDFLAGS = -lm `sdl2-config --libs` -lSDL2_ttf

# Folder to bundle all runtime files
BUNDLE_DIR = bundle
LIBS_TO_COPY = \
    $(shell ldd $(TARGET) | grep -E 'SDL2|SDL2_ttf' | awk '{print $$3}')

# Build the program
build: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

# Bundle target: copies executable and required libraries
bundle: build
	mkdir -p $(BUNDLE_DIR)
	cp $(TARGET) $(BUNDLE_DIR)/
	ldd $(TARGET) | grep -E 'SDL2|SDL2_ttf' | awk '{print $$3}' | while read lib; do cp -u "$$lib" $(BUNDLE_DIR)/; done

# Debug build
gdb: CFLAGS += -g
gdb: build
	$(DB) $(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET