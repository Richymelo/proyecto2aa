#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "Sudoku.h"
#include <gtk/gtk.h>

// Estructura para el contexto del solucionador
typedef struct {
    Sudoku *sudoku;
    GtkWidget *cells[9][9];
    GtkWidget *timer_label;
    GtkWidget *status_label;
    GtkWidget *btn_leer;
    GtkWidget *btn_grabar;
    GtkWidget *btn_resolver;
    
    int resolviendo;
    int solucion_encontrada;
    struct timespec start_time;
    int timer_id;
} SolverContext;

// Función principal de resolución usando backtracking
int resolver_sudoku(SolverContext *context);

// Función auxiliar para el algoritmo de backtracking
int backtrack_sudoku(SolverContext *context, int fila, int columna);

// Función para actualizar la interfaz durante la resolución
void actualizar_celda_solver(SolverContext *context, int fila, int columna, int valor);

// Función para procesar eventos GTK durante la resolución
gboolean procesar_eventos_solver(gpointer data);

#endif // SUDOKU_SOLVER_H

