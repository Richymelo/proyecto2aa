# Solucionador de Sudoku - Proyecto 2

**Curso:** Análisis de Algoritmos  
**Institución:** Instituto Tecnológico de Costa Rica  
**Semestre:** II Semestre 2025  

## Descripción

Implementación de un solucionador de Sudoku utilizando el algoritmo de backtracking con interfaz gráfica desarrollada en GTK+3 y Glade. El proyecto cumple con todos los requisitos especificados para el análisis de algoritmos.

## Características

- **Algoritmo:** Backtracking clásico según especificaciones
- **Interfaz:** GTK+3 con diseño en Glade
- **Visualización:** Actualización en tiempo real del proceso de resolución
- **Precisión:** Timer con resolución de milisegundos
- **Funcionalidades:** Cargar/guardar archivos, validación visual

## Requisitos del Sistema

- **SO:** Linux
- **Compilador:** GCC con soporte C99
- **Dependencias:** GTK+3, pkg-config

### Instalación de Dependencias

```bash
# Ubuntu/Debian
sudo apt-get install libgtk-3-dev pkg-config build-essential

# Fedora/CentOS  
sudo dnf install gtk3-devel pkg-config gcc make

# Arch Linux
sudo pacman -S gtk3 pkg-config gcc make
```

## Compilación y Ejecución

```bash
# Compilar
make

# Ejecutar
./sudoku_solver

# Ejecutar sin warnings
make run-silent

# Limpiar archivos compilados
make clean
```

## Estructura del Proyecto

```
proyecto2aa/
├── sudoku_solver.c           # Archivo principal
├── Sudoku.c/.h               # Estructura de datos Sudoku
├── SudokuSolver.c/.h         # Algoritmo de backtracking
├── sudoku_solver.glade       # Interfaz Glade
├── sudoku_style.css          # Estilos CSS
├── sample_sudoku.txt         # Ejemplo de Sudoku
├── Makefile                  # Configuración de compilación
└── README.md                 # Documentación
```

## Algoritmo de Backtracking

El algoritmo implementa la lógica especificada:

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

## Validaciones

Para cada dígito en posición [i][j]:
- No repetido en fila i
- No repetido en columna j
- No repetido en subsección 3x3

## Formato de Archivos

Los archivos de Sudoku utilizan formato texto:
- 9 líneas, 9 números por línea
- 0 para celdas vacías, 1-9 para pistas
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

## Generación de Interfaz Completa

Para generar el archivo Glade completo con las 81 celdas:

```bash
chmod +x generate_complete_glade.sh
./generate_complete_glade.sh
```

## Cumplimiento de Requisitos

✅ Código en C  
✅ Algoritmo de backtracking especificado  
✅ Interfaz GTK+3 y Glade  
✅ Compilación en Linux  
✅ Actualización constante durante resolución  
✅ Timer de alta precisión  
✅ Funcionalidad guardar/cargar  
✅ Validación completa  
✅ Sin errores de segmentación  
✅ Interfaz profesional  

## Uso del Programa

1. Ejecutar `./sudoku_solver`
2. Cargar un Sudoku con "Leer"
3. Hacer clic en "Resolver" para ver el algoritmo en acción
4. Guardar el resultado con "Grabar"

---

**Desarrollado para:** Curso de Análisis de Algoritmos - TEC 2025