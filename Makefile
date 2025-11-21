TARGET := Demo

SRC_DIR := src
CORE_DIR := $(SRC_DIR)/core
BUILD_DIR := build
BIN_DIR := bin

CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O0 -g

SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_image)
SDL_LDFLAGS := $(shell pkg-config --libs sdl2 SDL2_image)

# Source files
CORE_SRCS := $(wildcard $(CORE_DIR)/*.cpp)
ROOT_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(CORE_SRCS) $(ROOT_SRCS)

# Object files
CORE_OBJS := $(CORE_SRCS:$(SRC_DIR)/core/%.cpp=$(BUILD_DIR)/core/%.o)
ROOT_OBJS := $(ROOT_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS := $(CORE_OBJS) $(ROOT_OBJS)

all: $(BIN_DIR)/$(TARGET)

# Link
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SDL_LDFLAGS)

# Compile src/core/*.cpp
$(BUILD_DIR)/core/%.o: $(SRC_DIR)/core/%.cpp
	@mkdir -p $(BUILD_DIR)/core
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Compile src/*.cpp (like main.cpp)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run
run: all
	./$(BIN_DIR)/$(TARGET)

.PHONY: all clean run
