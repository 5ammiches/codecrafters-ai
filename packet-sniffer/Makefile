# Packet Sniffer - Makefile

CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = -lpcap

# Source files
SRC_DIR = src
BUILD_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target
TARGET = sniffer

# AddressSanitizer (use: make ASAN=1)
ifdef ASAN
    CFLAGS += -fsanitize=address -fno-omit-frame-pointer
    LDFLAGS += -fsanitize=address
endif

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run (requires sudo)
run: $(TARGET)
	sudo ./$(TARGET)

# Memory check with valgrind
memcheck: $(TARGET)
	sudo valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./$(TARGET)

# Format code
format:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h 2>/dev/null || true

.PHONY: all clean run memcheck format
