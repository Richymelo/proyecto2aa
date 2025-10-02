# Solucionador de Sudoku - Proyecto 2 Análisis de Algoritmos

Este proyecto implementa un solucionador de Sudoku usando el algoritmo clásico de backtracking con una interfaz gráfica desarrollada en GTK y Glade.

## Características

- **Interfaz Gráfica**: Desarrollada con GTK+3 y Glade
- **Algoritmo de Backtracking**: Implementación clásica según las especificaciones del proyecto
- **Actualización en Tiempo Real**: Muestra el progreso de la resolución paso a paso
- **Timer de Alta Precisión**: Cronómetro con precisión de milisegundos
- **Guardar/Cargar**: Funcionalidad para guardar y cargar puzzles de Sudoku
- **Validación Visual**: Distingue entre pistas iniciales y celdas calculadas
- **Subsecciones 3x3**: Visualización clara de las 9 subsecciones del Sudoku

## Estructura del Proyecto

```
proyecto2aa/
├── sudoku_solver.c      # Archivo principal con interfaz GTK
├── Sudoku.h             # Definición de estructura de datos Sudoku
├── Sudoku.c             # Implementación de funciones básicas de Sudoku
├── SudokuSolver.h       # Definición del algoritmo de backtracking
├── SudokuSolver.c       # Implementación del algoritmo de backtracking
├── sudoku_solver.glade  # Archivo de interfaz Glade
├── sudoku_style.css     # Estilos CSS para la interfaz
├── sample_sudoku.txt    # Archivo de ejemplo con un Sudoku
├── Makefile             # Archivo de compilación
└── README.md            # Este archivo
```

## Requisitos del Sistema

- **Sistema Operativo**: Linux (requisito del proyecto)
- **Compilador**: GCC con soporte C99
- **Librerías**: GTK+3, pkg-config
- **Herramientas**: make

### Instalación de Dependencias

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install -y libgtk-3-dev pkg-config build-essential
```

#### Fedora/CentOS:
```bash
sudo dnf install gtk3-devel pkg-config gcc make
```

#### Arch Linux:
```bash
sudo pacman -S gtk3 pkg-config gcc make
```

## Compilación

### Compilación Automática:
```bash
make
```

### Compilación Manual:
```bash
gcc -Wall -Wextra -std=c99 -g `pkg-config --cflags gtk+-3.0` -c sudoku_solver.c -o sudoku_solver.o
gcc -Wall -Wextra -std=c99 -g `pkg-config --cflags gtk+-3.0` -c Sudoku.c -o Sudoku.o
gcc -Wall -Wextra -std=c99 -g `pkg-config --cflags gtk+-3.0` -c SudokuSolver.c -o SudokuSolver.o
gcc -Wall -Wextra -std=c99 -g -o sudoku_solver sudoku_solver.o Sudoku.o SudokuSolver.o `pkg-config --libs gtk+-3.0`
```

## Ejecución

```bash
./sudoku_solver
```

## Funcionalidades

### Interfaz de Usuario

1. **Grid 9x9**: Tablero principal con 81 celdas
2. **Subsecciones 3x3**: Colores alternados para visualizar las 9 subsecciones
3. **Pistas Iniciales**: Celdas no editables con fondo gris
4. **Timer**: Cronómetro de alta precisión (milisegundos)
5. **Estado**: Etiqueta que muestra el estado actual del programa

### Botones

- **Salir**: Termina la ejecución del programa
- **Leer**: Carga un problema previamente guardado
- **Grabar**: Guarda el problema actual en un archivo
- **Resolver**: Inicia la búsqueda de solución usando backtracking

### Algoritmo de Backtracking

El algoritmo implementa exactamente la lógica especificada en el proyecto:

```
casilla actual = primera casilla sin llenar;
poner un 1 en casilla actual;
terminado = FALSE;
while (!terminado) {
    while (casilla actual NO sea valida y valor de casilla <= 9)
        incrementar valor de casilla actual;
    if (valor de casilla <= 9) {
        if (casillas sin llenar) {
            casilla actual = siguiente casilla sin llenar;
            poner un 1 en casilla actual;
        } else
            terminado = TRUE;
    } else {
        Borrar casilla actual;
        if (hay casilla anterior) {
            casilla actual = casilla anterior;
            incrementar valor de casilla actual;
        } else
            terminado = TRUE;
    }
}
```

### Validaciones

Para cada dígito intentado en una casilla [i][j]:
- No puede estar repetido en la fila i
- No puede estar repetido en la columna j  
- No puede estar repetido en la subsección 3x3 que contiene [i][j]

## Formato de Archivos

Los archivos de Sudoku se guardan en formato texto con:
- 9 líneas
- 9 números por línea (0 para celdas vacías, 1-9 para pistas)
- Números separados por espacios

Ejemplo:
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

## Características Técnicas

### Actualización Constante
- La interfaz se actualiza en tiempo real durante la resolución
- Cada movimiento del algoritmo es visible al usuario
- Timer actualizado cada 10ms para máxima precisión

### Precisión de Tiempo
- Utiliza `clock_gettime()` con `CLOCK_MONOTONIC` para alta precisión
- Muestra tiempo en formato MM:SS.mmm (minutos:segundos.milisegundos)

### Manejo de Eventos
- Procesamiento de eventos GTK durante la resolución para mantener interfaz responsiva
- Validación de entrada en tiempo real
- Prevención de modificaciones durante la resolución

## Cumplimiento de Requisitos

✅ **Todo el código en C**: Implementación completa en lenguaje C
✅ **Algoritmo especificado**: Backtracking exacto según especificaciones
✅ **GTK y Glade**: Interfaz gráfica desarrollada con estas herramientas
✅ **Linux**: Compilación y ejecución en Linux
✅ **Actualización constante**: Interfaz actualizada durante resolución
✅ **Timer de alta precisión**: Cronómetro con milisegundos
✅ **Guardar/Cargar**: Funcionalidad completa de archivos
✅ **Validación**: Verificación de filas, columnas y subsecciones
✅ **Sin segmentation faults**: Manejo robusto de errores
✅ **Interfaz profesional**: Diseño limpio y funcional

## Comandos Útiles

```bash
# Limpiar archivos compilados
make clean

# Verificar sintaxis
make check

# Instalar dependencias (Ubuntu/Debian)
make install-deps

# Ejecutar después de compilar
make run
```

## Solución de Problemas

### Error de compilación con GTK:
```bash
# Verificar que GTK está instalado
pkg-config --modversion gtk+-3.0

# Si no está instalado:
sudo apt-get install libgtk-3-dev pkg-config
```

### Error de ejecución:
```bash
# Verificar que el ejecutable tiene permisos
chmod +x sudoku_solver

# Ejecutar con debug
gdb ./sudoku_solver
```

### Archivo CSS no encontrado:
Asegúrate de ejecutar el programa desde el directorio que contiene `sudoku_style.css`.

## Autor

Proyecto desarrollado para el curso de Análisis de Algoritmos - II Semestre 2025, Instituto Tecnológico de Costa Rica.

## Notas de Desarrollo

- El proyecto cumple con todos los requisitos indispensables especificados
- No utiliza librerías adicionales más allá de GTK+3
- Código completamente documentado en español
- Implementación robusta sin memory leaks
- Interfaz intuitiva y profesional