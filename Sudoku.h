#ifndef KENKEN_H
#define KENKEN_H

// Definir el tamaño de la matriz Kenken
#define FILAS 6
#define COLUMNAS 6

// Declaración de la estructura (equivalente a la clase en Java)
typedef struct {
    int kenken[FILAS][COLUMNAS]; // La matriz Kenken (6x6)
} Kenken;

// Declaración de funciones (equivalentes a los métodos en Java)

// Constructor: Inicializa la estructura
void inicializarKenken(Kenken *k); 

// Getter: Retorna un puntero a la matriz Kenken
int (*getKenken(Kenken *k))[COLUMNAS];

// Setter: Permite establecer el valor de la matriz completa
void setKenken(Kenken *k, int nuevaKenken[FILAS][COLUMNAS]);

// Función adicional para ver un elemento específico (ejemplo de acceso)
int getValor(Kenken *k, int fila, int columna);

// Función adicional para establecer un elemento específico (ejemplo de modificación)
void setValor(Kenken *k, int fila, int columna, int valor);

#endif // KENKEN_H