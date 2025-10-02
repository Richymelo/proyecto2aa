@echo off
echo Compilando proyecto Kenken en C...

REM Intentar con GCC primero
gcc -Wall -Wextra -std=c99 -g -o kenken.exe MenuPrincipal.c Sudoku.c SudokuBoard.c TableroNumeros.c 2>nul
if %errorlevel% equ 0 (
    echo Compilacion exitosa con GCC!
    echo Ejecutable creado: kenken.exe
    goto :end
)

REM Si GCC no esta disponible, intentar con cl (Visual Studio)
cl /W3 /std:c99 /Fe:kenken.exe MenuPrincipal.c Sudoku.c SudokuBoard.c TableroNumeros.c 2>nul
if %errorlevel% equ 0 (
    echo Compilacion exitosa con Visual Studio C!
    echo Ejecutable creado: kenken.exe
    goto :end
)

echo Error: No se encontro un compilador de C disponible.
echo Por favor instale GCC (MinGW) o Visual Studio.
echo.
echo Para instalar MinGW:
echo 1. Descargue MinGW-w64 de https://www.mingw-w64.org/
echo 2. Agregue el directorio bin al PATH del sistema
echo 3. Reinicie la terminal

:end
pause

