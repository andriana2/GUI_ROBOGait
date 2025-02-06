#!/bin/bash

# Lista de archivos a compilar y ejecutar
archivos=(
    # "reducir_punto.cpp"
    # "bezier.cpp"
    "filtro_puntos.cpp"
    # "suavizarTrayectoriaChaikin.cpp"
    # "chaikin.cpp"
    # "suavizarTrayectoriaKalman.cpp"
    # "suavizarTrayectoriaMediaMovil.cpp"
    # "trayectoria_corner_cutting.cpp"
    # "corner_cutting.cpp"
)

# Compilar y ejecutar cada archivo
for archivo in "${archivos[@]}"; do
    nombre_salida="${archivo%.cpp}"  # Eliminar extensión .cpp
    echo "Compilando $archivo..."
    g++ "$archivo" -o "$nombre_salida" `pkg-config --cflags --libs opencv4`
    
    if [ $? -eq 0 ]; then
        echo "Ejecutando $nombre_salida..."
        ./"$nombre_salida"
    else
        echo "Error al compilar $archivo"
    fi
done
