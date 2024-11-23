#include "../include/utils.h"

#include <stdexcept>

// #include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>

std::string moveToString(Move move) {
    switch(move) {
    case Recto: return "Recto";
    case Atras: return "Atras";
    case Giro_Izquierda: return "Giro_Izquierda";
    case Giro_Derecha: return "Giro_Derecha";
    case Mas_Rapido: return "Mas_Rapido";
    case Mas_Lento: return "Mas_Lento";
    default: return "Desconocido";
    }
}

// Función que convierte un string a un valor enum Move
Move stringToMove(const std::string& str) {
    if (str == "Recto") return Recto;
    else if (str == "Atras") return Atras;
    else if (str == "Giro_Izquierda") return Giro_Izquierda;
    else if (str == "Giro_Derecha") return Giro_Derecha;
    else if (str == "Mas_Rapido") return Mas_Rapido;
    else if (str == "Mas_Lento") return Mas_Lento;
    throw std::invalid_argument("Valor desconocido para Move: ");
}

std::string obtenerIP() {
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *tempAddr = nullptr;
    std::string ipAddress = "No se pudo obtener la IP";

    // Obtener lista de interfaces
    if (getifaddrs(&interfaces) == 0) {
        tempAddr = interfaces;
        // Recorrer las interfaces
        while (tempAddr != nullptr) {
            if (tempAddr->ifa_addr->sa_family == AF_INET) { // Solo IPv4
                // Verificar que la interfaz no sea "localhost"
                if (strcmp(tempAddr->ifa_name, "lo") != 0) {
                    ipAddress = inet_ntoa(((struct sockaddr_in*)tempAddr->ifa_addr)->sin_addr);
                    break;
                }
            }
            tempAddr = tempAddr->ifa_next;
        }
    }
    freeifaddrs(interfaces); // Liberar la memoria asignada
    return ipAddress;
}
