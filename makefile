CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++11
SRC_DIR := .
BUILD_DIR := build
BIN_DIR := bin
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET := $(BIN_DIR)/game
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
.PHONY: all clean
