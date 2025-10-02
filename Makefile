# Makefile para el proyecto Sudoku Solver en C con GTK

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = `pkg-config --libs gtk+-3.0`
TARGET = sudoku_solver
SOURCES = sudoku_solver.c Sudoku.c SudokuSolver.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = Sudoku.h SudokuSolver.h

# Regla principal
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(GTK_LIBS)

# Compilar archivos objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Verificar sintaxis sin compilar
check:
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -fsyntax-only $(SOURCES)

# Instalar dependencias (para Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y libgtk-3-dev pkg-config

.PHONY: all clean run check install-deps

