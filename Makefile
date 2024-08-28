# Define variables
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = 
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=build/%.o)
EXEC = cafe.bin

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

# Compile source files into object files
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(EXEC) $(OBJECTS)

# compile and run
run:
	@$(MAKE) && ./$(EXEC) $(ARGS)

# # Run tests
# test: $(EXEC)
# 	./tests/test_program

# Phony targets (not actual files)
.PHONY: all clean test run
