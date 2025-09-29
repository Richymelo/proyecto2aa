#include "sudokuboard.h"
#include <string.h> // Para funciones como memset o memcpy

// Implementación de las funciones

void iniciarComponentes(SudokuBoard *board) {
    // Inicialización de atributos (simulando la de Java)
    board->txtAncho = 70;
    board->txtAltura = 70;
    board->txtMargen = 4;
    board->txtTamannoLetra = 27;
    
    board->panelBackground = COLOR_BLACK;
    board->txtBackground1 = COLOR_WHITE;
    board->txtForeground1 = COLOR_BLACK;
    board->txtBackground2 = COLOR_WHITE;
    board->txtForeground2 = COLOR_BLACK;
    board->txtBackground3 = COLOR_WHITE;
    board->txtForeground3 = COLOR_BLACK;
    
    // Inicializar la estructura Kenken
    inicializarKenken(&board->kenken);
    
    // Inicializar contadores de arrays auxiliares
    board->listaTxtAux_count = 0;
    board->listaTxtGenerados_count = 0;
    board->txtSelected = NULL; // Ninguna celda seleccionada inicialmente
}

void inicializarSudokuBoard(SudokuBoard *board) {
    // Llama a la función de inicialización de atributos
    iniciarComponentes(board);
    // Nota: initComponents() en Java es para inicialización automática, aquí se hace explícitamente.
}

// **Función sin implementación de GUI real en C puro**
void crearCamposTxt(SudokuBoard *board) {
    printf("Creando campos de texto (simulado). Se necesita una librería GUI.\n");
    int x = board->txtMargen;
    int y = board->txtMargen;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *txt = &board->listaTxt[i][j];
            
            // Simulación de las propiedades del JTextField:
            txt->valor = 0; // Campo vacío
            txt->background = board->txtBackground1;
            txt->foreground = board->txtForeground1;
            txt->editable = 0; 
            
            // En un entorno GUI real, aquí crearías un widget y lo asociarías a txt->widget_ptr
            
            // Simulación de posicionamiento (para entender la lógica):
            // txt->x = x;
            // txt->y = y;
            // txt->ancho = board->txtAncho;
            // txt->altura = board->txtAltura;

            x += board->txtAncho;
            
            // Aquí iría el código para asociar eventos (simulación de generarEventos(txt))
        }
        x = board->txtMargen;
        y += board->txtAltura;
    }
}

// **Función sin implementación de GUI real en C puro**
void crearKenken(SudokuBoard *board) {
    printf("Configurando el tablero Kenken (simulado).\n");
    // La lógica de Java: this.setLayout(null);, this.setSize(...);, this.setBackground(...);
    // Esto se maneja con funciones específicas de la librería GUI elegida.
    
    // Lógica para crear las celdas
    crearCamposTxt(board);
}

// Lógica de `pressed(JTextField txt)`
void pressed(SudokuBoard *board, Cell *txt) {
    // 1. Limpiar la selección anterior
    for (int k = 0; k < board->listaTxtAux_count; k++) {
        board->listaTxtAux[k]->background = board->txtBackground1;
        board->listaTxtAux[k]->foreground = board->txtForeground1;
        // En una GUI real, aquí se actualizaría la apariencia del widget real
    }
    board->listaTxtAux_count = 0; // Limpia el ArrayList
    
    // 2. Buscar la celda seleccionada (i, j)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (&board->listaTxt[i][j] == txt) {
                // 3. Resaltar la fila y la columna
                for (int k = 0; k < BOARD_SIZE; k++) {
                    // Resaltar columna
                    Cell *col_cell = &board->listaTxt[k][j];
                    col_cell->background = board->txtBackground2;
                    col_cell->foreground = board->txtForeground2;
                    board->listaTxtAux[board->listaTxtAux_count++] = col_cell;
                    
                    // Resaltar fila
                    Cell *row_cell = &board->listaTxt[i][k];
                    row_cell->background = board->txtBackground2;
                    row_cell->foreground = board->txtForeground2;
                    board->listaTxtAux[board->listaTxtAux_count++] = row_cell;
                }
                
                // 4. Resaltar la celda seleccionada
                txt->background = board->txtBackground3;
                txt->foreground = board->txtForeground3;
                // En una GUI real, aquí se actualizaría la apariencia y borde del widget
                
                board->txtSelected = txt;
                return;
            }
        }
    }
}

// Lógica de `keyPressed(KeyEvent e)` para números 1-9
void manejarTecla(SudokuBoard *board, Cell *txt, char key_char) {
    if (key_char >= '1' && key_char <= '6') { // Asumo un Kenken 6x6 (números 1 a 6)
        // Convertir el carácter a entero (si lo necesitas para la lógica)
        int valor = key_char - '0'; 
        
        // Actualizar el valor en la celda
        txt->valor = valor;
        
        // En una GUI real, aquí se actualizaría el texto del widget:
        // setText(String.valueOf(e.getKeyChar()));
    }
}