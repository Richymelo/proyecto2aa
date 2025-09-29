#include "kenken.h" // Incluye la definición de la estructura y funciones
#include <stdio.h>
#include <string.h> // Para la función memcpy

// Constructor: Inicializa la estructura Kenken con ceros
void inicializarKenken(Kenken *k) {
    // Inicialización directa (similar a la de Java)
    int kenk_inicial[FILAS][COLUMNAS] = {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    
    // Copiar la matriz inicial a la matriz de la estructura

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            k->kenken[i][j] = 0;
        }
    }
    
}

// Getter: Retorna un puntero a la matriz Kenken
// La sintaxis de retorno 'int (*...)[COLUMNAS]' es un puntero a un array de COLUMNAS enteros.
int (*getKenken(Kenken *k))[COLUMNAS] {
    return k->kenken;
}

// Setter: Permite establecer el valor de la matriz completa
void setKenken(Kenken *k, int nuevaKenken[FILAS][COLUMNAS]) {
    // Usamos memcpy para copiar el contenido de la matriz de entrada
    memcpy(k->kenken, nuevaKenken, sizeof(int) * FILAS * COLUMNAS);
}

// Función para obtener un valor específico
int getValor(Kenken *k, int fila, int columna) {
    // Es buena práctica añadir validación de límites aquí
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        return k->kenken[fila][columna];
    }
    return -1; // Valor de error o manejo apropiado
}

// Función para establecer un valor específico
void setValor(Kenken *k, int fila, int columna, int valor) {
    // Es buena práctica añadir validación de límites aquí
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        k->kenken[fila][columna] = valor;
    }
}