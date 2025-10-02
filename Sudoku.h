#ifndef SUDOKU_H
#define SUDOKU_H

// Definir el tamaño de la matriz Sudoku
#define FILAS 9
#define COLUMNAS 9
#define SUBSECTION_SIZE 3

// Declaración de la estructura para Sudoku
typedef struct {
    int sudoku[FILAS][COLUMNAS]; // La matriz Sudoku (9x9)
    int original[FILAS][COLUMNAS]; // Matriz original con pistas iniciales
} Sudoku;

// Declaración de funciones para Sudoku

// Constructor: Inicializa la estructura
void inicializarSudoku(Sudoku *s); 

// Getter: Retorna un puntero a la matriz Sudoku
int (*getSudoku(Sudoku *s))[COLUMNAS];

// Setter: Permite establecer el valor de la matriz completa
void setSudoku(Sudoku *s, int nuevaSudoku[FILAS][COLUMNAS]);

// Función para ver un elemento específico
int getValor(Sudoku *s, int fila, int columna);

// Función para establecer un elemento específico
void setValor(Sudoku *s, int fila, int columna, int valor);

// Función para verificar si una celda es válida
int esValido(Sudoku *s, int fila, int columna, int valor);

// Función para verificar si el Sudoku está completo
int estaCompleto(Sudoku *s);

// Función para encontrar la siguiente celda vacía
int encontrarCeldaVacia(Sudoku *s, int *fila, int *columna);

// Función para copiar la matriz original
void copiarOriginal(Sudoku *s);

// Función para verificar si una celda es pista inicial
int esPistaInicial(Sudoku *s, int fila, int columna);

#endif // SUDOKU_H