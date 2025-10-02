#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Sudoku.h"
#include "SudokuSolver.h"

// Estructura para almacenar datos de la aplicación
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *cells[9][9];
    GtkWidget *timer_label;
    GtkWidget *status_label;
    GtkWidget *btn_salir;
    GtkWidget *btn_leer;
    GtkWidget *btn_grabar;
    GtkWidget *btn_resolver;
    
    Sudoku sudoku;
    int resolviendo;
    int timer_id;
    struct timespec start_time;
    SolverContext solver_context;
} AppData;

// Función para actualizar el timer
static gboolean __attribute__((unused)) update_timer(gpointer data) {
    // This function is currently unused but kept for potential future use
    (void)data; // Suppress unused parameter warning
    AppData *app = (AppData*)data;
    
    if (!app->resolviendo) {
        return G_SOURCE_CONTINUE;
    }
    
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    
    long elapsed_ns = (current_time.tv_sec - app->start_time.tv_sec) * 1000000000L + 
                     (current_time.tv_nsec - app->start_time.tv_nsec);
    
    double elapsed_seconds = elapsed_ns / 1000000000.0;
    int minutes = (int)(elapsed_seconds / 60);
    int seconds = (int)(elapsed_seconds) % 60;
    int milliseconds = (int)((elapsed_seconds - (int)elapsed_seconds) * 1000);
    
    char time_str[32];
    snprintf(time_str, sizeof(time_str), "Tiempo: %02d:%02d.%03d", minutes, seconds, milliseconds);
    gtk_label_set_text(GTK_LABEL(app->timer_label), time_str);
    
    return G_SOURCE_CONTINUE;
}

// Función para actualizar la interfaz con el estado del Sudoku
void actualizar_interfaz(AppData *app) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int valor = getValor(&app->sudoku, i, j);
            char texto[2];
            if (valor == 0) {
                texto[0] = '\0';
            } else {
                texto[0] = '0' + valor;
                texto[1] = '\0';
            }
            gtk_entry_set_text(GTK_ENTRY(app->cells[i][j]), texto);
            
            // Marcar pistas iniciales como no editables
            if (esPistaInicial(&app->sudoku, i, j)) {
                gtk_editable_set_editable(GTK_EDITABLE(app->cells[i][j]), FALSE);
                gtk_widget_set_name(app->cells[i][j], "pista-inicial");
            } else {
                gtk_editable_set_editable(GTK_EDITABLE(app->cells[i][j]), TRUE);
                gtk_widget_set_name(app->cells[i][j], "celda-normal");
            }
        }
    }
}

// Función para cargar un Sudoku desde archivo
void cargar_sudoku(AppData *app, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(app->status_label), "Error: No se pudo abrir el archivo");
        return;
    }
    
    inicializarSudoku(&app->sudoku);
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int valor;
            if (fscanf(file, "%d", &valor) == 1) {
                setValor(&app->sudoku, i, j, valor);
            }
        }
    }
    
    fclose(file);
    copiarOriginal(&app->sudoku);
    actualizar_interfaz(app);
    gtk_label_set_text(GTK_LABEL(app->status_label), "Sudoku cargado exitosamente");
}

// Función para guardar un Sudoku a archivo
void guardar_sudoku(AppData *app, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(app->status_label), "Error: No se pudo crear el archivo");
        return;
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int valor = getValor(&app->sudoku, i, j);
            fprintf(file, "%d", valor);
            if (j < 8) fprintf(file, " ");
        }
        if (i < 8) fprintf(file, "\n");
    }
    
    fclose(file);
    gtk_label_set_text(GTK_LABEL(app->status_label), "Sudoku guardado exitosamente");
}

// Función de callback para resolver
static void resolver_callback(GtkWidget *widget __attribute__((unused)), gpointer data) {
    AppData *app = (AppData*)data;
    
    if (app->resolviendo) {
        return; // Ya se está resolviendo
    }
    
    // Configurar contexto del solver
    app->solver_context.sudoku = &app->sudoku;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            app->solver_context.cells[i][j] = app->cells[i][j];
        }
    }
    app->solver_context.timer_label = app->timer_label;
    app->solver_context.status_label = app->status_label;
    app->solver_context.btn_leer = app->btn_leer;
    app->solver_context.btn_grabar = app->btn_grabar;
    app->solver_context.btn_resolver = app->btn_resolver;
    app->solver_context.resolviendo = 1;
    app->solver_context.solucion_encontrada = 0;
    
    // Iniciar resolución
    resolver_sudoku(&app->solver_context);
}

// Función de callback para salir
static void salir_callback(GtkWidget *widget __attribute__((unused)), gpointer data) {
    AppData *app = (AppData*)data;
    
    if (app->timer_id) {
        g_source_remove(app->timer_id);
    }
    
    gtk_main_quit();
}

// Función de callback para leer archivo
static void leer_callback(GtkWidget *widget __attribute__((unused)), gpointer data) {
    AppData *app = (AppData*)data;
    
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    
    dialog = gtk_file_chooser_dialog_new("Abrir archivo de Sudoku",
                                        GTK_WINDOW(app->window),
                                        action,
                                        "_Cancelar", GTK_RESPONSE_CANCEL,
                                        "_Abrir", GTK_RESPONSE_ACCEPT,
                                        NULL);
    
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        cargar_sudoku(app, filename);
        g_free(filename);
    }
    
    gtk_widget_destroy(dialog);
}

// Función de callback para grabar archivo
static void grabar_callback(GtkWidget *widget __attribute__((unused)), gpointer data) {
    AppData *app = (AppData*)data;
    
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;
    
    dialog = gtk_file_chooser_dialog_new("Guardar archivo de Sudoku",
                                        GTK_WINDOW(app->window),
                                        action,
                                        "_Cancelar", GTK_RESPONSE_CANCEL,
                                        "_Guardar", GTK_RESPONSE_ACCEPT,
                                        NULL);
    
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        guardar_sudoku(app, filename);
        g_free(filename);
    }
    
    gtk_widget_destroy(dialog);
}

// Función para manejar entrada de texto en celdas
static void on_cell_changed(GtkWidget *widget, gpointer data) {
    AppData *app = (AppData*)data;
    
    if (app->resolviendo) {
        return; // No permitir cambios mientras se resuelve
    }
    
    // Encontrar qué celda fue modificada
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (app->cells[i][j] == widget) {
                const char *text = gtk_entry_get_text(GTK_ENTRY(widget));
                int valor = 0;
                
                if (strlen(text) > 0) {
                    valor = text[0] - '0';
                    if (valor < 1 || valor > 9) {
                        valor = 0;
                        gtk_entry_set_text(GTK_ENTRY(widget), "");
                    }
                }
                
                setValor(&app->sudoku, i, j, valor);
                return;
            }
        }
    }
}

// Función para crear la interfaz principal
void crear_interfaz(AppData *app) {
    // Cargar CSS
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    
    gtk_css_provider_load_from_path(css_provider, "sudoku_style.css", NULL);
    gtk_style_context_add_provider_for_screen(screen,
                                            GTK_STYLE_PROVIDER(css_provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    // Crear ventana principal
    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "Solucionador de Sudoku");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 600, 700);
    gtk_window_set_resizable(GTK_WINDOW(app->window), FALSE);
    g_signal_connect(app->window, "destroy", G_CALLBACK(salir_callback), app);
    
    // Crear contenedor principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(app->window), vbox);
    
    // Crear etiqueta de timer
    app->timer_label = gtk_label_new("Tiempo: 00:00.000");
    gtk_box_pack_start(GTK_BOX(vbox), app->timer_label, FALSE, FALSE, 0);
    
    // Crear grid principal para el Sudoku
    app->grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(app->grid), 2);
    gtk_grid_set_row_spacing(GTK_GRID(app->grid), 2);
    gtk_box_pack_start(GTK_BOX(vbox), app->grid, TRUE, TRUE, 10);
    
    // Crear las 81 celdas del Sudoku
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            app->cells[i][j] = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(app->cells[i][j]), 1);
            gtk_entry_set_alignment(GTK_ENTRY(app->cells[i][j]), 0.5);
            gtk_entry_set_width_chars(GTK_ENTRY(app->cells[i][j]), 2);
            
            // Aplicar estilos para mostrar las subsecciones 3x3
            // Alternar colores para las 9 subsecciones de 3x3
            int subsection = (i / 3) * 3 + (j / 3);
            if (subsection % 2 == 0) {
                gtk_widget_set_name(app->cells[i][j], "celda-clara");
            } else {
                gtk_widget_set_name(app->cells[i][j], "celda-oscura");
            }
            
            g_signal_connect(app->cells[i][j], "changed", G_CALLBACK(on_cell_changed), app);
            gtk_grid_attach(GTK_GRID(app->grid), app->cells[i][j], j, i, 1, 1);
        }
    }
    
    // Crear barra de botones
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    
    // Botón Salir
    app->btn_salir = gtk_button_new_with_label("Salir");
    g_signal_connect(app->btn_salir, "clicked", G_CALLBACK(salir_callback), app);
    gtk_box_pack_start(GTK_BOX(hbox), app->btn_salir, FALSE, FALSE, 0);
    
    // Botón Leer
    app->btn_leer = gtk_button_new_with_label("Leer");
    g_signal_connect(app->btn_leer, "clicked", G_CALLBACK(leer_callback), app);
    gtk_box_pack_start(GTK_BOX(hbox), app->btn_leer, FALSE, FALSE, 0);
    
    // Botón Grabar
    app->btn_grabar = gtk_button_new_with_label("Grabar");
    g_signal_connect(app->btn_grabar, "clicked", G_CALLBACK(grabar_callback), app);
    gtk_box_pack_start(GTK_BOX(hbox), app->btn_grabar, FALSE, FALSE, 0);
    
    // Botón Resolver
    app->btn_resolver = gtk_button_new_with_label("Resolver");
    g_signal_connect(app->btn_resolver, "clicked", G_CALLBACK(resolver_callback), app);
    gtk_box_pack_start(GTK_BOX(hbox), app->btn_resolver, FALSE, FALSE, 0);
    
    // Etiqueta de estado
    app->status_label = gtk_label_new("Listo para comenzar");
    gtk_box_pack_start(GTK_BOX(vbox), app->status_label, FALSE, FALSE, 5);
}

// Función principal
int main(int argc, char *argv[]) {
    AppData app;
    
    // Suppress GTK warnings and debug messages
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc)gtk_false, NULL);
    g_log_set_handler("GLib-GObject", G_LOG_LEVEL_WARNING, (GLogFunc)gtk_false, NULL);
    g_log_set_handler("GLib", G_LOG_LEVEL_WARNING, (GLogFunc)gtk_false, NULL);
    
    gtk_init(&argc, &argv);
    
    // Inicializar datos de la aplicación
    app.resolviendo = 0;
    app.timer_id = 0;
    inicializarSudoku(&app.sudoku);
    
    // Crear interfaz
    crear_interfaz(&app);
    
    // Mostrar ventana
    gtk_widget_show_all(app.window);
    
    // Ejecutar bucle principal
    gtk_main();
    
    return 0;
}
