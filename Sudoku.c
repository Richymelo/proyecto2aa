#include "Sudoku.h"
#include <string.h>

// Constructor: Inicializa la estructura Sudoku con ceros
void inicializarSudoku(Sudoku *s) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            s->sudoku[i][j] = 0;
            s->original[i][j] = 0;
        }
    }
}

// Getter: Retorna un puntero a la matriz Sudoku
int (*getSudoku(Sudoku *s))[COLUMNAS] {
    return s->sudoku;
}

// Setter: Permite establecer el valor de la matriz completa
void setSudoku(Sudoku *s, int nuevaSudoku[FILAS][COLUMNAS]) {
    memcpy(s->sudoku, nuevaSudoku, sizeof(int) * FILAS * COLUMNAS);
}

// Función para obtener un valor específico
int getValor(Sudoku *s, int fila, int columna) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        return s->sudoku[fila][columna];
    }
    return -1;
}

// Función para establecer un valor específico
void setValor(Sudoku *s, int fila, int columna, int valor) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        s->sudoku[fila][columna] = valor;
    }
}

// Función para verificar si una celda es válida
int esValido(Sudoku *s, int fila, int columna, int valor) {
    // Verificar fila
    for (int j = 0; j < COLUMNAS; j++) {
        if (j != columna && s->sudoku[fila][j] == valor) {
            return 0;
        }
    }
    
    // Verificar columna
    for (int i = 0; i < FILAS; i++) {
        if (i != fila && s->sudoku[i][columna] == valor) {
            return 0;
        }
    }
    
    // Verificar subsección 3x3
    int inicioFila = (fila / SUBSECTION_SIZE) * SUBSECTION_SIZE;
    int inicioCol = (columna / SUBSECTION_SIZE) * SUBSECTION_SIZE;
    
    for (int i = inicioFila; i < inicioFila + SUBSECTION_SIZE; i++) {
        for (int j = inicioCol; j < inicioCol + SUBSECTION_SIZE; j++) {
            if ((i != fila || j != columna) && s->sudoku[i][j] == valor) {
                return 0;
            }
        }
    }
    
    return 1;
}

// Función para verificar si el Sudoku está completo
int estaCompleto(Sudoku *s) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (s->sudoku[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// Función para encontrar la siguiente celda vacía
int encontrarCeldaVacia(Sudoku *s, int *fila, int *columna) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (s->sudoku[i][j] == 0) {
                *fila = i;
                *columna = j;
                return 1;
            }
        }
    }
    return 0;
}

// Función para copiar la matriz original
void copiarOriginal(Sudoku *s) {
    memcpy(s->original, s->sudoku, sizeof(int) * FILAS * COLUMNAS);
}

// Función para verificar si una celda es pista inicial
int esPistaInicial(Sudoku *s, int fila, int columna) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        return s->original[fila][columna] != 0;
    }
    return 0;
}