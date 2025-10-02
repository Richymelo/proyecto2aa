#include "SudokuSolver.h"
#include <time.h>
#include <unistd.h>

// Función para actualizar la interfaz durante la resolución
void actualizar_celda_solver(SolverContext *context, int fila, int columna, int valor) {
    if (context->cells[fila][columna]) {
        char texto[2];
        if (valor == 0) {
            texto[0] = '\0';
        } else {
            texto[0] = '0' + valor;
            texto[1] = '\0';
        }
        
        // Actualizar la celda en la interfaz
        gtk_entry_set_text(GTK_ENTRY(context->cells[fila][columna]), texto);
        
        // Procesar eventos de GTK para actualizar la pantalla
        while (gtk_events_pending()) {
            gtk_main_iteration();
        }
        
        // Pequeña pausa para que se vea el proceso de resolución
        usleep(10000); // 10ms
    }
}

// Función para procesar eventos GTK durante la resolución
gboolean procesar_eventos_solver(gpointer data) {
    SolverContext *context = (SolverContext*)data;
    
    if (!context->resolviendo) {
        return G_SOURCE_REMOVE;
    }
    
    // Actualizar timer
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    
    long elapsed_ns = (current_time.tv_sec - context->start_time.tv_sec) * 1000000000L + 
                     (current_time.tv_nsec - context->start_time.tv_nsec);
    
    double elapsed_seconds = elapsed_ns / 1000000000.0;
    int minutes = (int)(elapsed_seconds / 60);
    int seconds = (int)(elapsed_seconds) % 60;
    int milliseconds = (int)((elapsed_seconds - (int)elapsed_seconds) * 1000);
    
    char time_str[32];
    snprintf(time_str, sizeof(time_str), "Tiempo: %02d:%02d.%03d", minutes, seconds, milliseconds);
    gtk_label_set_text(GTK_LABEL(context->timer_label), time_str);
    
    return G_SOURCE_CONTINUE;
}

// Función auxiliar para el algoritmo de backtracking
int backtrack_sudoku(SolverContext *context, int fila, int columna) {
    // Si hemos llegado al final, hemos encontrado una solución
    if (fila >= 9) {
        context->solucion_encontrada = 1;
        return 1;
    }
    
    // Si la celda ya tiene un valor (pista inicial), pasar a la siguiente
    if (getValor(context->sudoku, fila, columna) != 0) {
        int next_fila = fila;
        int next_columna = columna + 1;
        if (next_columna >= 9) {
            next_columna = 0;
            next_fila++;
        }
        return backtrack_sudoku(context, next_fila, next_columna);
    }
    
    // Probar valores del 1 al 9
    for (int valor = 1; valor <= 9 && !context->solucion_encontrada; valor++) {
        // Verificar si el valor es válido
        if (esValido(context->sudoku, fila, columna, valor)) {
            // Colocar el valor
            setValor(context->sudoku, fila, columna, valor);
            
            // Actualizar la interfaz
            actualizar_celda_solver(context, fila, columna, valor);
            
            // Verificar si el usuario quiere detener la resolución
            if (!context->resolviendo) {
                return 0;
            }
            
            // Calcular la siguiente posición
            int next_fila = fila;
            int next_columna = columna + 1;
            if (next_columna >= 9) {
                next_columna = 0;
                next_fila++;
            }
            
            // Continuar recursivamente
            if (backtrack_sudoku(context, next_fila, next_columna)) {
                return 1;
            }
            
            // Si llegamos aquí, el valor no llevó a una solución
            // Limpiar la celda (backtrack)
            setValor(context->sudoku, fila, columna, 0);
            actualizar_celda_solver(context, fila, columna, 0);
            
            // Verificar si el usuario quiere detener la resolución
            if (!context->resolviendo) {
                return 0;
            }
        }
    }
    
    return 0; // No se encontró solución con este camino
}

// Función principal de resolución usando backtracking
int resolver_sudoku(SolverContext *context) {
    context->solucion_encontrada = 0;
    context->resolviendo = 1;
    
    // Iniciar timer
    clock_gettime(CLOCK_MONOTONIC, &context->start_time);
    context->timer_id = g_timeout_add(10, procesar_eventos_solver, context);
    
    // Actualizar estado
    gtk_label_set_text(GTK_LABEL(context->status_label), "Resolviendo...");
    
    // Desactivar botones
    gtk_widget_set_sensitive(context->btn_leer, FALSE);
    gtk_widget_set_sensitive(context->btn_grabar, FALSE);
    gtk_widget_set_sensitive(context->btn_resolver, FALSE);
    
    // Iniciar el algoritmo de backtracking
    int resultado = backtrack_sudoku(context, 0, 0);
    
    // Detener timer
    if (context->timer_id) {
        g_source_remove(context->timer_id);
        context->timer_id = 0;
    }
    
    context->resolviendo = 0;
    
    // Reactivar botones
    gtk_widget_set_sensitive(context->btn_leer, TRUE);
    gtk_widget_set_sensitive(context->btn_grabar, TRUE);
    gtk_widget_set_sensitive(context->btn_resolver, TRUE);
    
    if (resultado && context->solucion_encontrada) {
        gtk_label_set_text(GTK_LABEL(context->status_label), "¡Sudoku resuelto!");
        
        // Calcular tiempo final
        struct timespec end_time;
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        
        long elapsed_ns = (end_time.tv_sec - context->start_time.tv_sec) * 1000000000L + 
                         (end_time.tv_nsec - context->start_time.tv_nsec);
        
        double elapsed_seconds = elapsed_ns / 1000000000.0;
        int minutes = (int)(elapsed_seconds / 60);
        int seconds = (int)(elapsed_seconds) % 60;
        int milliseconds = (int)((elapsed_seconds - (int)elapsed_seconds) * 1000);
        
        char final_time_str[64];
        snprintf(final_time_str, sizeof(final_time_str), 
                "Tiempo final: %02d:%02d.%03d", minutes, seconds, milliseconds);
        gtk_label_set_text(GTK_LABEL(context->timer_label), final_time_str);
        
        return 1;
    } else {
        gtk_label_set_text(GTK_LABEL(context->status_label), "No se encontró solución");
        return 0;
    }
}
