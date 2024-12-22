#include <QCoreApplication>
#include <QImage>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <cmath> // Para sin() y cos()

void actualizarMapa(const QString &rutaMapa, const QString &rutaSalida, 
                    double x_robot, double y_robot, double x_origen, double y_origen, 
                    double resolucion, double angulo) {
    // Cargar la imagen (acepta formatos como .pgm y .png)
    QImage mapa(rutaMapa);
    if (mapa.isNull()) {
        qWarning("Error al cargar el mapa");
        return;
    }

    // Convertir a formato ARGB32 si es necesario para permitir modificaciones
    if (mapa.format() != QImage::Format_ARGB32) {
        mapa = mapa.convertToFormat(QImage::Format_ARGB32);
    }

    // Calcular la posición del píxel para el punto del robot
    int columna = static_cast<int>((x_robot - x_origen) / resolucion);
    int fila = mapa.height() - 1 - static_cast<int>((y_robot - y_origen) / resolucion);

    // Verificar que la posición esté dentro de los límites de la imagen
    if (columna < 0 || columna >= mapa.width() || fila < 0 || fila >= mapa.height()) {
        qWarning("La posición del robot está fuera de los límites del mapa");
        return;
    }

    // Calcular el extremo de la flecha
    const double longitud_flecha = 5.0; // Longitud de la flecha en píxeles
    int columna_flecha = columna + static_cast<int>(longitud_flecha * std::cos(angulo));
    int fila_flecha = fila - static_cast<int>(longitud_flecha * std::sin(angulo)); // Invertir Y para coordenadas

    // Pintar en la imagen
    QPainter painter(&mapa);

    // Dibujar el punto rojo (posición del robot)
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(columna, fila), 2, 2); // Radio de 3 píxeles

    // Dibujar la flecha azul (dirección del robot)
    painter.setPen(QPen(Qt::blue, 1)); // Línea azul de 2 píxeles de ancho
    painter.drawLine(QPoint(columna, fila), QPoint(columna_flecha, fila_flecha));

    painter.end();

    // Guardar la imagen modificada en formato PNG
    if (!mapa.save(rutaSalida, "PNG")) {
        qWarning("Error al guardar el mapa modificado como PNG");
    } else {
        qDebug() << "Mapa modificado guardado como" << rutaSalida;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Ruta del mapa en formato PGM
    QString rutaMapa = "../temporal_map.pgm";

    // Ruta de salida en formato PNG
    QString rutaSalida = "../mi_mapa_modificado.png";

    // Coordenadas del robot (en metros)
    double x_robot = 1.9827 + 1.3532;     // Coordenada X del robot
    double y_robot = 0.5138 -0.448;     // Coordenada Y del robot
    double x_origen = -1.25;    // Origen del mapa en X
    double y_origen = -2.38;    // Origen del mapa en Y
    double resolucion = 0.05;   // Resolución del mapa (metros por píxel)

    // Ángulo del robot (en radianes, medido desde el eje positivo X, sentido antihorario)
    double angulo = 1; // 45 grados en radianes

    // Actualizar el mapa
    actualizarMapa(rutaMapa, rutaSalida, x_robot, y_robot, x_origen, y_origen, resolucion, angulo);

    return 0;
}

