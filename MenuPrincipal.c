#include <stdio.h>
#include "SudokuBoard.h"
#include "TableroNumeros.h"

// Estructura para el menú principal
typedef struct {
    int horas;
    int minutos;
    int segundos;
    int dificultad;
    SudokuBoard sudokuBoard;
    TableroNumeros tableroNumeros;
    int juegoActivo;
    int tiempoIniciado;
} MenuPrincipal;

// Función para inicializar el menú principal
void inicializarMenuPrincipal(MenuPrincipal *menu) {
    menu->horas = 0;
    menu->minutos = 0;
    menu->segundos = 0;
    menu->dificultad = 1; // 1 = Fácil, 2 = Medio, 3 = Difícil
    menu->juegoActivo = 0;
    menu->tiempoIniciado = 0;
    
    // Inicializar el tablero de Sudoku/Kenken
    inicializarSudokuBoard(&menu->sudokuBoard);
    
    // Inicializar el tablero de números
    inicializarTableroNumeros(&menu->tableroNumeros);
}

// Función para mostrar el menú principal
void mostrarMenu() {
    printf("\n=== KENKEN GAME ===\n");
    printf("1. Jugar\n");
    printf("2. Nuevo Juego\n");
    printf("3. Validar Juego\n");
    printf("4. Reiniciar\n");
    printf("5. Terminar Juego\n");
    printf("6. Deshacer\n");
    printf("7. Rehacer\n");
    printf("8. Cambiar Dificultad\n");
    printf("9. Salir\n");
    printf("Seleccione una opción: ");
}

// Función para contar atrás del tiempo
void cuentaAtras(MenuPrincipal *menu) {
    if (menu->segundos > 0) {
        menu->segundos--;
    } else if (menu->minutos > 0) {
        menu->segundos = 59;
        menu->minutos--;
    } else if (menu->horas > 0) {
        menu->segundos = 59;
        menu->minutos = 59;
        menu->horas--;
    } else {
        // Tiempo agotado
        printf("\n¡Tiempo agotado! El juego ha terminado.\n");
        menu->juegoActivo = 0;
    }
}

// Función para mostrar el cronómetro
void mostrarCronometro(MenuPrincipal *menu) {
    printf("\nTiempo: %02d:%02d:%02d\n", menu->horas, menu->minutos, menu->segundos);
}

// Función para jugar
void jugar(MenuPrincipal *menu) {
    printf("\n=== INICIANDO JUEGO ===\n");
    menu->juegoActivo = 1;
    menu->tiempoIniciado = 1;
    
    // Configurar tiempo inicial según dificultad
    switch (menu->dificultad) {
        case 1: // Fácil
            menu->horas = 1;
            menu->minutos = 0;
            menu->segundos = 0;
            break;
        case 2: // Medio
            menu->horas = 0;
            menu->minutos = 45;
            menu->segundos = 0;
            break;
        case 3: // Difícil
            menu->horas = 0;
            menu->minutos = 30;
            menu->segundos = 0;
            break;
    }
    
    printf("Nivel: ");
    switch (menu->dificultad) {
        case 1: printf("Fácil"); break;
        case 2: printf("Medio"); break;
        case 3: printf("Difícil"); break;
    }
    printf("\n");
    
    mostrarCronometro(menu);
    crearKenken(&menu->sudokuBoard);
    printf("¡Juego iniciado! Use los números 1-6 para llenar el tablero.\n");
}

// Función para nuevo juego
void nuevoJuego(MenuPrincipal *menu) {
    printf("\n=== NUEVO JUEGO ===\n");
    // Reiniciar el tablero
    inicializarSudokuBoard(&menu->sudokuBoard);
    
    // Reiniciar tiempo
    menu->horas = 0;
    menu->minutos = 0;
    menu->segundos = 0;
    menu->juegoActivo = 0;
    menu->tiempoIniciado = 0;
    
    printf("Tablero reiniciado. Presione '1' para comenzar un nuevo juego.\n");
}

// Función para validar juego
void validarJuego(MenuPrincipal *menu) {
    printf("\n=== VALIDANDO JUEGO ===\n");
    if (!menu->juegoActivo) {
        printf("No hay un juego activo para validar.\n");
        return;
    }
    
    // Aquí iría la lógica de validación del Kenken
    printf("Validación del juego completada.\n");
    // Por simplicidad, asumimos que el juego es válido
    printf("¡Felicidades! El juego es válido.\n");
}

// Función para reiniciar
void reiniciar(MenuPrincipal *menu) {
    printf("\n=== REINICIANDO JUEGO ===\n");
    if (!menu->juegoActivo) {
        printf("No hay un juego activo para reiniciar.\n");
        return;
    }
    
    // Reiniciar el tablero pero mantener el tiempo
    inicializarSudokuBoard(&menu->sudokuBoard);
    printf("Juego reiniciado. El tiempo continúa corriendo.\n");
}

// Función para terminar juego
void terminarJuego(MenuPrincipal *menu) {
    printf("\n=== TERMINANDO JUEGO ===\n");
    if (!menu->juegoActivo) {
        printf("No hay un juego activo para terminar.\n");
        return;
    }
    
    menu->juegoActivo = 0;
    menu->tiempoIniciado = 0;
    printf("Juego terminado. Tiempo final: ");
    mostrarCronometro(menu);
}

// Función para deshacer
void deshacer(MenuPrincipal *menu) {
    printf("\n=== DESHACIENDO ÚLTIMA JUGADA ===\n");
    if (!menu->juegoActivo) {
        printf("No hay un juego activo.\n");
        return;
    }
    printf("Última jugada deshecha.\n");
    // Aquí iría la lógica para deshacer la última jugada
}

// Función para rehacer
void rehacer(MenuPrincipal *menu) {
    printf("\n=== REHACIENDO JUGADA ===\n");
    if (!menu->juegoActivo) {
        printf("No hay un juego activo.\n");
        return;
    }
    printf("Jugada rehecha.\n");
    // Aquí iría la lógica para rehacer la última jugada deshecha
}

// Función para cambiar dificultad
void cambiarDificultad(MenuPrincipal *menu) {
    printf("\n=== CAMBIAR DIFICULTAD ===\n");
    printf("1. Fácil (60 minutos)\n");
    printf("2. Medio (45 minutos)\n");
    printf("3. Difícil (30 minutos)\n");
    printf("Seleccione dificultad: ");
    
    int nuevaDificultad;
    scanf("%d", &nuevaDificultad);
    
    if (nuevaDificultad >= 1 && nuevaDificultad <= 3) {
        menu->dificultad = nuevaDificultad;
        printf("Dificultad cambiada a: ");
        switch (menu->dificultad) {
            case 1: printf("Fácil\n"); break;
            case 2: printf("Medio\n"); break;
            case 3: printf("Difícil\n"); break;
        }
    } else {
        printf("Dificultad inválida. Manteniendo dificultad actual.\n");
    }
}

// Función para manejar entrada de números
void manejarEntradaNumero(MenuPrincipal *menu, int numero) {
    if (!menu->juegoActivo) {
        printf("No hay un juego activo. Presione '1' para iniciar un juego.\n");
        return;
    }
    
    if (numero >= 1 && numero <= 6) {
        printf("Número %d seleccionado para colocar en el tablero.\n", numero);
        // Aquí iría la lógica para colocar el número en la celda seleccionada
    } else {
        printf("Número inválido. Use números del 1 al 6.\n");
    }
}

// Función para mostrar el tablero
void mostrarTablero(MenuPrincipal *menu) {
    if (!menu->juegoActivo) {
        return;
    }
    
    printf("\n=== TABLERO KENKEN ===\n");
    // Aquí se mostraría el tablero actual
    // Por simplicidad, mostramos un tablero vacío
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("[ ] ");
        }
        printf("\n");
    }
    printf("\n");
}

// Función principal del juego
void ejecutarJuego(MenuPrincipal *menu) {
    int opcion;
    int numero;
    
    while (1) {
        if (menu->juegoActivo && menu->tiempoIniciado) {
            mostrarCronometro(menu);
        }
        
        mostrarMenu();
        
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada inválida. Intente de nuevo.\n");
            // Limpiar buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        switch (opcion) {
            case 1:
                jugar(menu);
                break;
            case 2:
                nuevoJuego(menu);
                break;
            case 3:
                validarJuego(menu);
                break;
            case 4:
                reiniciar(menu);
                break;
            case 5:
                terminarJuego(menu);
                break;
            case 6:
                deshacer(menu);
                break;
            case 7:
                rehacer(menu);
                break;
            case 8:
                cambiarDificultad(menu);
                break;
            case 9:
                printf("\n¡Gracias por jugar Kenken!\n");
                return;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
        
        // Si hay un juego activo, mostrar el tablero
        if (menu->juegoActivo) {
            mostrarTablero(menu);
            
            // Permitir entrada de números
            printf("Ingrese un número (1-6) para colocar en el tablero, o 0 para volver al menú: ");
            if (scanf("%d", &numero) == 1) {
                if (numero == 0) {
                    continue;
                } else {
                    manejarEntradaNumero(menu, numero);
                }
            }
        }
        
        printf("\n");
    }
}

// Función principal
int main() {
    printf("Bienvenido al juego Kenken en C!\n");
    
    MenuPrincipal menu;
    inicializarMenuPrincipal(&menu);
    
    ejecutarJuego(&menu);
    
    return 0;
}
