#include "../lib/utils.h"

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
