# Compiler
CC = gcc

# Flags do compilador
CFLAGS = -Wall

# Source directory
SRC_DIR = src

# Header directory
INC_DIR = include

# Object directory
OBJ_DIR = objs

# Nome do executavel
TARGET = sistema

# Main file
MAIN = main.c

# Sources 
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Objetos (usando patsubst para substituir corretamente o caminho dos arquivos .c para .o)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Default target (compile and run)
all: compile run

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all compile run clean

# Compile source files in the source directory into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	
# Rule to link object files and create the executable (target)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
