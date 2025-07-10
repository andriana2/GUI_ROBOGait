#include <opencv2/opencv.hpp>
#include <vector>

struct Punto {
    float x, y;
};

// Algoritmo de Corner Cutting para suavizar la trayectoria
std::vector<Punto> suavizarTrayectoriaCornerCutting(const std::vector<Punto>& puntos, int iteraciones, float alpha) {
    std::vector<Punto> resultado = puntos;

    for (int iter = 0; iter < iteraciones; ++iter) {
        std::vector<Punto> nuevaLista;

        for (size_t i = 0; i < resultado.size() - 1; ++i) {
            Punto p1 = resultado[i];
            Punto p2 = resultado[i + 1];

            // Punto más cerca de p1
            Punto q{
                (1 - alpha) * p1.x + alpha * p2.x,
                (1 - alpha) * p1.y + alpha * p2.y
            };

            // Punto más cerca de p2
            Punto r{
                alpha * p1.x + (1 - alpha) * p2.x,
                alpha * p1.y + (1 - alpha) * p2.y
            };

            nuevaLista.push_back(q);
            nuevaLista.push_back(r);
        }

        resultado = nuevaLista;
    }
    return resultado;
}

// Función para dibujar una trayectoria con un color específico
void dibujarTrayectoria(cv::Mat& imagen, const std::vector<Punto>& puntos, cv::Scalar color, int grosor) {
    for (size_t i = 1; i < puntos.size(); ++i) {
        cv::line(imagen, cv::Point(puntos[i - 1].x * 5, 500 - puntos[i - 1].y * 5),
                 cv::Point(puntos[i].x * 5, 500 - puntos[i].y * 5), color, grosor);
    }
}

int main() {
std::vector<Punto> puntosOriginales = {
{98,42},{97,39},{97,37},{97,36},{97,35},{97,34},{97,34},{97,33},{97,32},{97,31},
{96,30},{96,29},{96,28},{96,28},{96,27},{86,25},{85,25},{85,25},{84,25},{82,25},
{81,25},{79,25},{78,26},{77,26},{74,26},{73,27},{70,27},{68,27},{67,28},{65,28},
{63,28},{60,28},{59,28},{57,29},{56,29},{54,29},{53,29},{53,29},{52,29},{51,29},
{50,29},{48,29},{48,29},{46,29},{45,29},{44,29},{43,29},{42,29},{41,29},{40,29},
{39,29},{37,29},{37,29},{36,29},{35,29},{34,29},{33,29},{33,30},{33,31},{33,33},
{33,34},{33,36},{33,37},{33,39},{33,40},{33,41},{33,42},{33,44},{33,45},{32,47},
{32,48},{32,50},{32,51},{32,52},{32,54},{32,56},{32,57},{32,58},{32,59},{32,61},
{32,62},{32,63},{32,65},{32,66},{32,69},{32,71},{32,72},{32,73},{32,75},{33,77},
{33,78},{33,79},{33,80},{33,81},{33,82},{33,83},{33,84},{33,85},{34,85},{35,87},
{36,87},{37,87},{38,88},{38,88},{39,88},{40,89},{40,89},{41,90},{42,90},{43,90},
{44,90},{45,91},{45,91},{46,91},{46,91},{48,91},{50,91},{51,90},{52,90},{53,90},
{54,90},{56,90},{57,90},{58,89},{59,89},{60,89},{60,89},{61,89},{62,89},{63,89},
{64,90},{66,90},{67,90},{68,90},{68,90},{71,90},{73,90},{74,90},{75,90},{77,90},
{79,90},{82,89},{83,89},{84,89},{85,89},{87,89},{88,89},{89,89},{91,89},{92,90},
{93,90},{94,90},{98,78},{98,77},{98,75},{98,73},{98,73},{98,71},{98,71},{96,71},
{96,71},{94,71},{93,71},{92,70},{92,70},{91,70},{89,70},{88,70},{87,70},{84,70},
{83,70},{80,70},{79,70},{77,70},{76,70},{74,71},{73,71},{72,71},{71,71},{70,71},
{69,71},{67,71},{66,71},{65,71},{63,71},{62,71},{61,71},{60,71},{58,71},{57,71},
{56,71},{55,71},{54,71},{53,71},{53,71},{53,70},{53,69},{53,67},{53,66},{53,64},
{53,62},{53,60},{53,59},{53,58},{53,57},{53,55},{53,54},{53,53},{53,52},{53,52},
{53,51},{53,49},{53,49},{54,49},{55,49},{56,49},{57,49},{58,50},{59,50},{60,50},
{61,50},{63,50},{64,50},{65,50},{66,50},{68,50},{69,50},{70,50},{72,49},{74,49},
{75,49},{77,48},{78,48},{79,48},{81,48},{82,48},{83,48},{87,48}
};
    int iteraciones = 3;
    float alpha = 0.25; // Ajusta qué tan agresivo es el corte

    std::vector<Punto> puntosSuavizados = suavizarTrayectoriaCornerCutting(puntosOriginales, iteraciones, alpha);

    // Crear la imagen en negro
    cv::Mat imagen = cv::Mat::zeros(500, 500, CV_8UC3);

    // Dibujar la trayectoria original en rojo
    dibujarTrayectoria(imagen, puntosOriginales, cv::Scalar(0, 0, 255), 2); // Rojo

    // Dibujar la trayectoria suavizada en verde
    dibujarTrayectoria(imagen, puntosSuavizados, cv::Scalar(0, 255, 0), 2); // Verde

    // Mostrar la imagen con ambas trayectorias
    cv::imshow("Trayectoria Original (Rojo) vs Suavizada con Corner Cutting (Verde)", imagen);
    cv::waitKey(0);

    return 0;
}
