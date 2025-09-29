
#include "tableronumeros.h"
#include <stdio.h>

// Implementación de las funciones

// Inicia los valores de los atributos (iniciarComponentes en Java)
void iniciarComponentes(TableroNumeros *tablero) {
    tablero->txtAncho = 70;
    tablero->txtAltura = 70;
    tablero->txtMargen = 4;
    tablero->txtTamannoLetra = 27;
    
    tablero->panelBackground = COLOR_BLACK;
    tablero->txtBackground1 = COLOR_WHITE;
    tablero->txtForeground1 = COLOR_BLACK;
    tablero->txtBackground2 = COLOR_WHITE;
    tablero->txtForeground2 = COLOR_BLACK;
}

// Constructor (inicializa la estructura)
void inicializarTableroNumeros(TableroNumeros *tablero) {
    // La parte de initComponents() en Java es para la inicialización
    // automática; aquí llamamos a nuestra función de inicialización de atributos.
    iniciarComponentes(tablero);
}

// Configura el tablero (crearTablero en Java)
void crearTablero(TableroNumeros *tablero) {
    // Lógica de Java: this.setLayout(null);
    // En C, esto sería una llamada a una función de la librería GUI.
    
    // Lógica de Java: this.setSize(txtAncho+(2*txtMargen),txtAltura*9+(4*txtMargen));
    // Se calcula el tamaño, pero la aplicación del tamaño a la ventana
    // o panel se haría con la librería de GUI.
    int ancho_calculado = tablero->txtAncho + (2 * tablero->txtMargen);
    int alto_calculado = (tablero->txtAltura * 9) + (4 * tablero->txtMargen);
    printf("Tamaño del panel calculado: Ancho=%d, Alto=%d\n", ancho_calculado, alto_calculado);
    
    // Lógica de Java: this.setBackground(Color.BLACK);
    // En C, se usaría la función de la librería GUI para establecer el color de fondo.
    printf("Fondo del panel configurado a: Negro (0x%X)\n", tablero->panelBackground);
}

// Función placeholder para crear campos de texto (crearCamposTxt en Java)
void crearCamposTxt(TableroNumeros *tablero) {
    // La función original está vacía, por lo que aquí solo ponemos un placeholder.
    printf("Función crearCamposTxt ejecutada, pero no se creó ningún widget.\n");
}