#ifndef TABLERONUMEROS_H
#define TABLERONUMEROS_H

// Definición de colores (usando int para simplificar, como un valor RGB hexadecimal)
typedef int Color;
#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF

// Estructura principal (equivalente a la clase TableroNumeros)
typedef struct {
    // Atributos de la clase Java
    int txtAncho;
    int txtAltura;
    int txtMargen;
    int txtTamannoLetra;
    
    // Atributos de color
    Color panelBackground;
    Color txtBackground1;
    Color txtForeground1;
    Color txtBackground2;
    Color txtForeground2;

    // Aquí irían los arreglos de botones/campos de texto si los hubiera,
    // pero el código Java original los omite.
    // void* campos_txt_ptr[9]; // Ejemplo: Punteros a los 9 widgets si fueran 9 números
    
} TableroNumeros;

// Declaración de funciones (métodos)

// Constructor: Inicializa la estructura
void inicializarTableroNumeros(TableroNumeros *tablero);

// Inicia los valores de los atributos (equivalente a iniciarComponentes)
void iniciarComponentes(TableroNumeros *tablero);

// Configura el tablero (equivalente a crearTablero, pero sin GUI real)
// En una implementación real, esta función usaría la librería GUI para
// establecer el tamaño, diseño y color del widget padre.
void crearTablero(TableroNumeros *tablero);

// Función placeholder para crear campos de texto (equivalente a crearCamposTxt)
void crearCamposTxt(TableroNumeros *tablero);

#endif // TABLERONUMEROS_H