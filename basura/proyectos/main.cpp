#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <vector>

// Transformación de coordenadas físicas a píxeles
cv::Point calcularPixel(double x_robot, double y_robot, double x_origen, double y_origen, double resolucion) {
    int columna = static_cast<int>((x_robot - x_origen) / resolucion);
    int fila = static_cast<int>((y_robot - y_origen) / resolucion);
    return cv::Point(columna, fila);
}

int main() {
    // Cargar el mapa
    cv::Mat mapa = cv::imread("temporal_map.pgm", cv::IMREAD_GRAYSCALE);
    if (mapa.empty()) {
        std::cerr << "Error al cargar la imagen\n";
        return -1;
    }

    // Coordenadas y parámetros
    double x_robot = 2.2591, y_robot = -0.0357; // Posición del robot
    double x_origen = -1.25, y_origen = -2.38;  // Origen del mapa
    double resolucion = 0.05;                   // Resolución

    // Calcular la posición del píxel
    cv::Point pixel = calcularPixel(x_robot, y_robot, x_origen, y_origen, resolucion);

    // Pintar el punto en el mapa
    cv::circle(mapa, pixel, 1, cv::Scalar(200), -1); // Radio de 3 píxeles, color negro

    // Guardar la imagen modificada
    cv::imwrite("mi_mapa_modificado.pgm", mapa);

    // Enviar la imagen al cliente (pseudo-código)
    // Enviar por TCP o UDP según tu implementación de red.
    // ...
    return 0;
}