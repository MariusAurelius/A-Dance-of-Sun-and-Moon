# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -Wall -std=c++17
# Library paths
LIBS_PATH = ./lib
# Include paths
INCLUDES = -I./include -I./include/SDL2
# Libraries to link against
 LIBS = -L$(LIBS_PATH)/sdl2/lib -lSDL2 \
       -L$(LIBS_PATH)/sdl2_image/lib -lSDL2_image \
       -L$(LIBS_PATH)/sdl2_mixer/lib -lSDL2_mixer \
       -L$(LIBS_PATH)/sdl2_ttf/lib -lSDL2_ttf

# Source files
SRCS = $(wildcard src/*.cpp)

# Object files
OBJS = $(patsubst src/%.cpp, bin/%.o, $(SRCS))

# Executable
EXECUTABLE = bin/adosam

# Build rule for the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Build rule for object files
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXECUTABLE)