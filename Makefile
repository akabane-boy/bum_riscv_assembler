# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Iinclude

# Source and object files
SRC = src/main.c src/lexer.c src/parser.c src/lut.c src/encoder.c
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = bum_riscv_assembler

# Default build target
all: $(TARGET)

# Linking object files
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile .c to .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f src/*.o $(TARGET)

# run the assembler
run: $(TARGET)
	./$(TARGET)
