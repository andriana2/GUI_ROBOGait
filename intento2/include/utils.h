#ifndef UTILS_H
#define UTILS_H

// #include <iostream>
// #include <stdexcept>
#include <string>

enum Move {
    Recto,
    Atras,
    Giro_Izquierda,
    Giro_Derecha,
    Mas_Rapido,
    Mas_Lento
};

// Función que convierte el enum Move a un string
std::string MoveToString(Move move);

// Función que convierte un string a un valor enum Move
Move stringToMove(const std::string& str);

std::string obtenerIP();

#endif // UTILS_H
