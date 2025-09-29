#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <stdio.h> // Para entrada/salida
#include <stdlib.h> // Para funciones generales
#include "kenken.h" // Asume la definición de la estructura Kenken

// Dimensiones del tablero
#define BOARD_SIZE 6

// Definición de colores (usando int para simplificar, como un valor RGB)
// En una librería GUI, esto sería un tipo específico de esa librería.
typedef int Color;
#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF

// Estructura para representar una celda de texto (equivalente a JTextField)
typedef struct {
    int valor; // Almacena el número (1-6) o 0 si está vacío
    Color background;
    Color foreground;
    int editable; // 0=false, 1=true
    void* widget_ptr; // Puntero al objeto gráfico real (JTextField en Java, o widget de GTK/Qt en C)
} Cell;

// Estructura principal (equivalente a la clase SudokuBoard)
typedef struct {
    // Atributos de la clase
    Cell listaTxt[BOARD_SIZE][BOARD_SIZE]; // El arreglo 2D de celdas
    int txtAncho;
    int txtAltura;
    int txtMargen;
    int txtTamannoLetra;
    Color panelBackground;
    Color txtBackground1, txtForeground1;
    Color txtBackground2, txtForeground2;
    Color txtBackground3, txtForeground3;

    Kenken kenken; // La estructura de datos Kenken
    
    // Arrays auxiliares (simulando ArrayList<JTextField>)
    Cell* listaTxtAux[BOARD_SIZE * BOARD_SIZE]; // Usamos un array de punteros
    int listaTxtAux_count; 
    Cell* listaTxtGenerados[BOARD_SIZE * BOARD_SIZE];
    int listaTxtGenerados_count;
    Cell* txtSelected; // Puntero a la celda seleccionada
} SudokuBoard;

// Declaración de funciones (métodos)

// Constructor: Inicializa la estructura
void inicializarSudokuBoard(SudokuBoard *board);

// Inicia los valores de los atributos
void iniciarComponentes(SudokuBoard *board);

// Crea el tablero de Kenken (configura el panel y llama a crearCamposTxt)
// REQUIERE una librería GUI para la implementación real
void crearKenken(SudokuBoard *board);

// Crea y posiciona las celdas de texto
// REQUIERE una librería GUI para la implementación real
void crearCamposTxt(SudokuBoard *board);

// Simulación de la lógica de eventos al hacer clic
void pressed(SudokuBoard *board, Cell *txt);

// Simulación de la lógica de entrada de teclado
void manejarTecla(SudokuBoard *board, Cell *txt, char key_char);

#endif // SUDOKUBOARD_H