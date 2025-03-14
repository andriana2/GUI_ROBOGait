#include "../include/utils_ddbb.h"


std::string quote(const std::string &value)
{
    std::string escaped = value;

    // Escapar comillas simples reemplazándolas por dobles comillas simples (' -> '')
    size_t pos = 0;
    while ((pos = escaped.find("'", pos)) != std::string::npos) {
        escaped.replace(pos, 1, "''");
        pos += 2; // Avanzar después del reemplazo
    }

    // Envolver el valor entre comillas simples
    return "'" + escaped + "'";
}

std::string quote(int value) {
    return std::to_string(value);
}

std::string quote(double value) {
    return std::to_string(value);
}
