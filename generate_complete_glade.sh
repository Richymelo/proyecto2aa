#!/bin/bash

# Script para generar el archivo Glade completo con las 81 celdas del Sudoku
# Este script debe ejecutarse en Linux

echo "Generando archivo Glade completo con 81 celdas..."

# Función para determinar la clase CSS basada en la subsección 3x3
get_css_class() {
    local row=$1
    local col=$2
    local subsection=$(( (row / 3) * 3 + (col / 3) ))
    if [ $((subsection % 2)) -eq 0 ]; then
        echo "celda-clara"
    else
        echo "celda-oscura"
    fi
}

# Crear el archivo Glade
cat > sudoku_solver.glade << 'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.38.2 -->
<interface>
  <requires lib="gtk+" version="3.24"/>
  <object class="GtkWindow" id="window">
    <property name="width-request">600</property>
    <property name="height-request">700</property>
    <property name="can-focus">False</property>
    <property name="resizable">False</property>
    <property name="window-position">center</property>
    <property name="title">Solucionador de Sudoku</property>
    <child>
      <object class="GtkBox">
        <property name="visible">True</property>
        <property name="can-focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">5</property>
        <child>
          <object class="GtkLabel" id="timer_label">
            <property name="visible">True</property>
            <property name="can-focus">False</property>
            <property name="label">Tiempo: 00:00.000</property>
            <property name="justify">center</property>
            <attributes>
              <attribute name="weight" value="bold"/>
              <attribute name="scale" value="1.2"/>
            </attributes>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="sudoku_grid">
            <property name="visible">True</property>
            <property name="can-focus">False</property>
            <property name="margin">10</property>
            <property name="column-spacing">2</property>
            <property name="row-spacing">2</property>
            <property name="column-homogeneous">True</property>
            <property name="row-homogeneous">True</property>
EOF

# Generar las 81 celdas
for row in {0..8}; do
    for col in {0..8}; do
        css_class=$(get_css_class $row $col)
        cat >> sudoku_solver.glade << EOF
            <child>
              <object class="GtkEntry" id="cell_${row}_${col}">
                <property name="visible">True</property>
                <property name="can-focus">True</property>
                <property name="max-length">1</property>
                <property name="width-chars">2</property>
                <property name="xalign">0.5</property>
                <property name="name">${css_class}</property>
              </object>
              <packing>
                <property name="left-attach">${col}</property>
                <property name="top-attach">${row}</property>
              </packing>
            </child>
EOF
    done
done

# Completar el archivo
cat >> sudoku_solver.glade << 'EOF'
          </object>
          <packing>
            <property name="expand">True</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox">
            <property name="visible">True</property>
            <property name="can-focus">False</property>
            <property name="orientation">horizontal</property>
            <property name="spacing">5</property>
            <property name="homogeneous">True</property>
            <child>
              <object class="GtkButton" id="btn_salir">
                <property name="label" translatable="yes">Salir</property>
                <property name="visible">True</property>
                <property name="can-focus">True</property>
                <property name="receives-default">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_leer">
                <property name="label" translatable="yes">Leer</property>
                <property name="visible">True</property>
                <property name="can-focus">True</property>
                <property name="receives-default">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_grabar">
                <property name="label" translatable="yes">Grabar</property>
                <property name="visible">True</property>
                <property name="can-focus">True</property>
                <property name="receives-default">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_resolver">
                <property name="label" translatable="yes">Resolver</property>
                <property name="visible">True</property>
                <property name="can-focus">True</property>
                <property name="receives-default">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">3</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">2</property>
          </packing>
        </child>
        <child>
          <object class="GtkLabel" id="status_label">
            <property name="visible">True</property>
            <property name="can-focus">False</property>
            <property name="label">Listo para comenzar</property>
            <property name="justify">center</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">3</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
EOF

echo "✓ Archivo Glade completo generado con 81 celdas!"
echo "✓ Todas las celdas tienen las clases CSS correctas (celda-clara/celda-oscura)"
echo "✓ El archivo está listo para usar en Linux"


