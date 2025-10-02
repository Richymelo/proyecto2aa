#!/bin/bash

# Script para probar la compilación del Sudoku Solver
# Este script debe ejecutarse en un sistema Linux con GTK instalado

echo "=== Probando compilación del Sudoku Solver ==="

# Verificar que estamos en Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo "ERROR: Este proyecto debe compilarse en Linux"
    exit 1
fi

# Verificar que GTK está instalado
if ! pkg-config --exists gtk+-3.0; then
    echo "ERROR: GTK+3 no está instalado"
    echo "Instale con: sudo apt-get install libgtk-3-dev pkg-config"
    exit 1
fi

echo "✓ Sistema Linux detectado"
echo "✓ GTK+3 disponible"

# Limpiar compilaciones anteriores
echo "Limpiando archivos anteriores..."
make clean

# Verificar sintaxis
echo "Verificando sintaxis..."
if make check; then
    echo "✓ Sintaxis correcta"
else
    echo "✗ Errores de sintaxis encontrados"
    exit 1
fi

# Compilar
echo "Compilando..."
if make; then
    echo "✓ Compilación exitosa"
else
    echo "✗ Error en la compilación"
    exit 1
fi

# Verificar que el ejecutable existe
if [ -f "sudoku_solver" ]; then
    echo "✓ Ejecutable creado: sudoku_solver"
    echo "✓ Tamaño: $(du -h sudoku_solver | cut -f1)"
else
    echo "✗ Ejecutable no encontrado"
    exit 1
fi

echo ""
echo "=== Compilación completada exitosamente ==="
echo "Para ejecutar: ./sudoku_solver"
echo "Para probar con el archivo de ejemplo:"
echo "  1. Ejecutar ./sudoku_solver"
echo "  2. Hacer clic en 'Leer'"
echo "  3. Seleccionar 'sample_sudoku.txt'"
echo "  4. Hacer clic en 'Resolver'"
