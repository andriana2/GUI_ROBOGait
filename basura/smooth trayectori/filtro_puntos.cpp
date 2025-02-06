#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

struct Punto
{
    int x, y;
};
Punto bezierCubic(const Punto& p0, const Punto& p1, const Punto& p2, const Punto& p3, double t) {
    double u = 1 - t;
    double tt = t * t;
    double uu = u * u;
    double uuu = uu * u;
    double ttt = tt * t;

    Punto p;
    p.x = uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x;
    p.y = uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y;
    return p;
}

// Genera una trayectoria suavizada con Bézier
std::vector<Punto> suavizarBezier(const std::vector<Punto>& puntos, int subdivisiones = 10) {
    if (puntos.size() < 4) return puntos;

    std::vector<Punto> resultado;
    for (size_t i = 0; i < puntos.size() - 3; i += 3) {
        for (int j = 0; j <= subdivisiones; ++j) {
            double t = j / static_cast<double>(subdivisiones);
            resultado.push_back(bezierCubic(puntos[i], puntos[i + 1], puntos[i + 2], puntos[i + 3], t));
        }
    }
    return resultado;
}


void dibujarTrayectoria(cv::Mat &imagen, const std::vector<Punto> &puntos, cv::Scalar color, int grosor)
{
    for (size_t i = 1; i < puntos.size(); ++i)
    {
        cv::line(imagen, cv::Point(puntos[i - 1].x * 5, 500 - puntos[i - 1].y * 5),
                 cv::Point(puntos[i].x * 5, 500 - puntos[i].y * 5), color, grosor);
    }
}

double calcularAngulo(const Punto& p1, const Punto& p2, const Punto& p3) {
    double v1x = p2.x - p1.x;
    double v1y = p2.y - p1.y;
    double v2x = p3.x - p2.x;
    double v2y = p3.y - p2.y;

    double dot = v1x * v2x + v1y * v2y;
    double mag1 = std::sqrt(v1x * v1x + v1y * v1y);
    double mag2 = std::sqrt(v2x * v2x + v2y * v2y);

    if (mag1 == 0 || mag2 == 0) return 0;

    double cosTheta = dot / (mag1 * mag2);
    return std::acos(std::max(-1.0, std::min(1.0, cosTheta)));
}

// Filtro de puntos basado en giros bruscos
std::vector<Punto> filtrarPuntos(const std::vector<Punto>& puntos, double umbralAngulo) {
    if (puntos.size() < 3) return puntos;

    std::vector<Punto> resultado;
    resultado.push_back(puntos.front());

    for (size_t i = 1; i < puntos.size() - 1; ++i) {
        double angulo = calcularAngulo(puntos[i - 1], puntos[i], puntos[i + 1]);

        if (angulo < umbralAngulo) {
            resultado.push_back(puntos[i]);
        }
    }

    resultado.push_back(puntos.back());
    return resultado;
}

// Función para calcular la distancia perpendicular de un punto a una línea definida por dos puntos
double distanciaPerpendicular(const Punto& a, const Punto& b, const Punto& p) {
    double numerador = std::abs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x);
    double denominador = std::sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
    return numerador / denominador;
}

// Filtrado basado en distancia perpendicular
void filtrarPorDistancia(std::vector<Punto>& puntos, size_t inicio, size_t fin, double umbral, std::vector<Punto>& resultado) {
    if (fin <= inicio + 1) return;

    // Buscar el punto con la mayor distancia perpendicular
    size_t indiceMax = inicio;
    double maxDistancia = 0;

    for (size_t i = inicio + 1; i < fin; ++i) {
        double d = distanciaPerpendicular(puntos[inicio], puntos[fin], puntos[i]);
        if (d > maxDistancia) {
            maxDistancia = d;
            indiceMax = i;
        }
    }

    // Si la distancia máxima es mayor al umbral, mantener el punto y continuar con la división
    if (maxDistancia > umbral) {
        filtrarPorDistancia(puntos, inicio, indiceMax, umbral, resultado);
        resultado.push_back(puntos[indiceMax]);
        filtrarPorDistancia(puntos, indiceMax, fin, umbral, resultado);
    }
}

// Función principal para simplificar la trayectoria
std::vector<Punto> simplificarTrayectoria(const std::vector<Punto>& puntos, double umbral) {
    if (puntos.size() < 3) return puntos;

    std::vector<Punto> resultado;
    resultado.push_back(puntos.front()); // Primer punto siempre se mantiene
    filtrarPorDistancia(const_cast<std::vector<Punto>&>(puntos), 0, puntos.size() - 1, umbral, resultado);
    resultado.push_back(puntos.back()); // Último punto siempre se mantiene
    return resultado;
}

double distanciaPuntoLinea(Punto p, Punto a, Punto b)
{
    double area = std::abs((b.x - a.x) * (a.y - p.y) - (a.x - p.x) * (b.y - a.y));
    double base = std::hypot(b.x - a.x, b.y - a.y);
    return base == 0 ? 0 : area / base;
}

void DouglasPeucker(const std::vector<Punto> &puntos, double umbral, std::vector<Punto> &resultado)
{
    if (puntos.size() < 3)
    {
        resultado.insert(resultado.end(), puntos.begin(), puntos.end());
        return;
    }

    size_t maxIndex = 0;
    double maxDist = 0;

    for (size_t i = 1; i < puntos.size() - 1; ++i)
    {
        double dist = distanciaPuntoLinea(puntos[i], puntos.front(), puntos.back());
        if (dist > maxDist)
        {
            maxDist = dist;
            maxIndex = i;
        }
    }

    if (maxDist > umbral)
    {
        std::vector<Punto> left, right;
        std::vector<Punto> leftResult, rightResult;

        left.insert(left.begin(), puntos.begin(), puntos.begin() + maxIndex + 1);
        right.insert(right.begin(), puntos.begin() + maxIndex, puntos.end());

        DouglasPeucker(left, umbral, leftResult);
        DouglasPeucker(right, umbral, rightResult);

        resultado.insert(resultado.end(), leftResult.begin(), leftResult.end() - 1);
        resultado.insert(resultado.end(), rightResult.begin(), rightResult.end());
    }
    else
    {
        resultado.push_back(puntos.front());
        resultado.push_back(puntos.back());
    }
}

// std::vector<Punto> reducirPuntosAdaptativo(const std::vector<Punto> &puntos, double umbral)
// {
//     std::vector<Punto> resultado;
//     if (puntos.empty())
//         return resultado;

//     resultado.push_back(puntos.front()); // Agregar el primer punto

//     for (size_t i = 1; i < puntos.size(); ++i)
//     {
//         double distancia = std::hypot(puntos[i].x - resultado.back().x, puntos[i].y - resultado.back().y);
//         if (distancia > umbral)
//         {
//             resultado.push_back(puntos[i]);
//         }
//     }

//     return resultado;
// }

// std::vector<Punto> filtroMedianaMovil(const std::vector<Punto> &puntos, int ventana)
// {
//     std::vector<Punto> resultado = puntos;
//     for (size_t i = ventana / 2; i < puntos.size() - ventana / 2; ++i)
//     {
//         std::vector<int> xVec, yVec;
//         for (int j = -ventana / 2; j <= ventana / 2; ++j)
//         {
//             xVec.push_back(puntos[i + j].x);
//             yVec.push_back(puntos[i + j].y);
//         }
//         std::sort(xVec.begin(), xVec.end());
//         std::sort(yVec.begin(), yVec.end());
//         resultado[i] = {xVec[xVec.size() / 2], yVec[yVec.size() / 2]};
//     }
//     return resultado;
// }

std::vector<Punto> eliminarDuplicados(const std::vector<Punto> &puntos)
{
    std::vector<Punto> resultado;
    for (size_t i = 0; i < puntos.size(); ++i)
    {
        if (i == 0 || puntos[i].x != puntos[i - 1].x || puntos[i].y != puntos[i - 1].y)
        {
            resultado.push_back(puntos[i]);
        }
    }
    return resultado;
}

std::vector<Punto> filtrarPorCurvatura(const std::vector<Punto>& puntos, double umbral) {
    if (puntos.size() < 3) return puntos; // Si hay menos de 3 puntos, no se puede filtrar

    std::vector<Punto> resultado;
    resultado.push_back(puntos.front()); // Primer punto siempre se mantiene

    for (size_t i = 1; i < puntos.size() - 1; ++i) {
        double angulo = calcularAngulo(puntos[i - 1], puntos[i], puntos[i + 1]);

        if (angulo > umbral) { // Solo mantener puntos con alta curvatura
            resultado.push_back(puntos[i]);
        }
    }

    resultado.push_back(puntos.back()); // Último punto siempre se mantiene
    return resultado;
}

// std::vector<Punto> suavizarTrayectoriaCornerCutting(const std::vector<Punto>& puntos, int iteraciones, float alpha) {
//     std::vector<Punto> resultado = puntos;

//     for (int iter = 0; iter < iteraciones; ++iter) {
//         std::vector<Punto> nuevaLista;

//         for (size_t i = 0; i < resultado.size() - 1; ++i) {
//             Punto p1 = resultado[i];
//             Punto p2 = resultado[i + 1];

//             // Punto más cerca de p1
//             Punto q{
//                 (1 - alpha) * p1.x + alpha * p2.x,
//                 (1 - alpha) * p1.y + alpha * p2.y
//             };

//             // Punto más cerca de p2
//             Punto r{
//                 alpha * p1.x + (1 - alpha) * p2.x,
//                 alpha * p1.y + (1 - alpha) * p2.y
//             };

//             nuevaLista.push_back(q);
//             nuevaLista.push_back(r);
//         }

//         resultado = nuevaLista;
//     }
//     return resultado;
// }

int main()
{
    std::vector<Punto> puntosOriginales = {
        {98, 42}, {98, 42}, {98, 41}, {98, 41}, {98, 40}, {97, 40}, {97, 40}, {97, 39}, {97, 39}, {97, 39}, {97, 38}, {97, 38}, {97, 37}, {97, 37}, {97, 37}, {97, 36}, {97, 36}, {97, 36}, {97, 36}, {97, 35}, {97, 35}, {97, 35}, {97, 35}, {97, 35}, {97, 34}, {97, 34}, {97, 34}, {97, 34}, {97, 34}, {97, 34}, {97, 33}, {97, 33}, {97, 33}, {97, 33}, {97, 33}, {97, 33}, {97, 32}, {97, 32}, {97, 32}, {97, 32}, {97, 31}, {97, 31}, {97, 31}, {97, 31}, {96, 31}, {96, 30}, {96, 30}, {96, 30}, {96, 30}, {96, 30}, {96, 30}, {96, 29}, {96, 29}, {96, 29}, {96, 29}, {96, 28}, {96, 28}, {96, 28}, {96, 28}, {96, 28}, {96, 28}, {96, 28}, {96, 27}, {96, 27}, {96, 27}, {96, 27}, {96, 27}, {96, 27}, {96, 27}, {96, 26}, {95, 26}, {95, 26}, {95, 26}, {95, 26}, {94, 26}, {94, 26}, {94, 26}, {94, 26}, {93, 26}, {93, 26}, {93, 25}, {92, 25}, {92, 25}, {92, 25}, {92, 25}, {92, 25}, {91, 25}, {91, 25}, {91, 25}, {91, 25}, {90, 25}, {90, 25}, {90, 25}, {90, 25}, {89, 25}, {89, 25}, {89, 25}, {89, 25}, {89, 25}, {88, 25}, {88, 25}, {88, 25}, {88, 25}, {87, 25}, {87, 25}, {87, 25}, {87, 25}, {87, 25}, {86, 25}, {86, 25}, {86, 25}, {86, 25}, {85, 25}, {85, 25}, {85, 25}, {85, 25}, {85, 25}, {84, 25}, {84, 25}, {84, 25}, {84, 25}, {84, 25}, {83, 25}, {83, 25}, {83, 25}, {82, 25}, {82, 25}, {82, 25}, {81, 25}, {81, 25}, {81, 25}, {80, 25}, {80, 25}, {80, 25}, {80, 25}, {80, 25}, {79, 25}, {79, 25}, {79, 25}, {79, 26}, {79, 26}, {78, 26}, {78, 26}, {78, 26}, {77, 26}, {77, 26}, {77, 26}, {76, 26}, {76, 26}, {75, 26}, {74, 26}, {74, 26}, {74, 26}, {73, 27}, {73, 27}, {73, 27}, {72, 27}, {71, 27}, {70, 27}, {70, 27}, {69, 27}, {68, 27}, {67, 27}, {67, 28}, {67, 28}, {66, 28}, {66, 28}, {66, 28}, {65, 28}, {65, 28}, {64, 28}, {64, 28}, {63, 28}, {63, 28}, {62, 28}, {62, 28}, {61, 28}, {61, 28}, {61, 28}, {60, 28}, {60, 28}, {60, 28}, {59, 28}, {59, 28}, {59, 28}, {59, 28}, {58, 29}, {58, 29}, {57, 29}, {57, 29}, {57, 29}, {56, 29}, {56, 29}, {56, 29}, {55, 29}, {55, 29}, {55, 29}, {54, 29}, {54, 29}, {54, 29}, {54, 29}, {53, 29}, {53, 29}, {53, 29}, {53, 29}, {53, 29}, {53, 29}, {52, 29}, {52, 29}, {52, 29}, {52, 29}, {51, 29}, {51, 29}, {51, 29}, {51, 29}, {51, 29}, {50, 29}, {50, 29}, {50, 29}, {50, 29}, {50, 29}, {50, 29}, {49, 29}, {49, 29}, {49, 29}, {49, 29}, {49, 29}, {48, 29}, {48, 29}, {48, 29}, {48, 29}, {48, 29}, {47, 29}, {47, 29}, {47, 29}, {46, 29}, {46, 29}, {46, 29}, {45, 29}, {45, 29}, {45, 29}, {45, 29}, {45, 29}, {44, 29}, {44, 29}, {44, 29}, {44, 29}, {43, 29}, {43, 29}, {43, 29}, {43, 29}, {42, 29}, {42, 29}, {42, 29}, {42, 29}, {41, 29}, {41, 29}, {41, 29}, {41, 29}, {40, 29}, {40, 29}, {40, 29}, {40, 29}, {39, 29}, {39, 29}, {39, 29}, {39, 29}, {38, 29}, {38, 29}, {38, 29}, {38, 29}, {37, 29}, {37, 29}, {37, 29}, {37, 29}, {37, 29}, {36, 29}, {36, 29}, {36, 29}, {36, 29}, {35, 29}, {35, 29}, {35, 29}, {34, 29}, {34, 29}, {34, 29}, {33, 29}, {33, 29}, {33, 29}, {33, 29}, {33, 29}, {33, 30}, {33, 30}, {33, 30}, {33, 31}, {33, 31}, {33, 31}, {33, 32}, {33, 32}, {33, 32}, {33, 33}, {33, 33}, {33, 33}, {33, 34}, {33, 34}, {33, 34}, {33, 34}, {33, 35}, {33, 35}, {33, 35}, {33, 35}, {33, 35}, {33, 36}, {33, 36}, {33, 37}, {33, 37}, {33, 37}, {33, 37}, {33, 38}, {33, 38}, {33, 38}, {33, 39}, {33, 39}, {33, 39}, {33, 39}, {33, 39}, {33, 40}, {33, 40}, {33, 40}, {33, 40}, {33, 41}, {33, 41}, {33, 41}, {33, 41}, {33, 42}, {33, 42}, {33, 43}, {33, 43}, {33, 43}, {33, 44}, {33, 44}, {33, 44}, {33, 45}, {33, 45}, {33, 45}, {33, 45}, {33, 46}, {33, 46}, {32, 47}, {32, 47}, {32, 47}, {32, 48}, {32, 48}, {32, 49}, {32, 49}, {32, 49}, {32, 50}, {32, 50}, {32, 50}, {32, 50}, {32, 50}, {32, 51}, {32, 51}, {32, 51}, {32, 51}, {32, 52}, {32, 52}, {32, 52}, {32, 52}, {32, 53}, {32, 53}, {32, 54}, {32, 54}, {32, 54}, {32, 55}, {32, 55}, {32, 56}, {32, 56}, {32, 56}, {32, 56}, {32, 57}, {32, 57}, {32, 57}, {32, 57}, {32, 57}, {32, 58}, {32, 58}, {32, 58}, {32, 59}, {32, 59}, {32, 59}, {32, 59}, {32, 60}, {32, 60}, {32, 60}, {32, 61}, {32, 61}, {32, 61}, {32, 61}, {32, 62}, {32, 62}, {32, 62}, {32, 62}, {32, 63}, {32, 63}, {32, 63}, {32, 63}, {32, 63}, {32, 64}, {32, 64}, {32, 64}, {32, 65}, {32, 65}, {32, 65}, {32, 66}, {32, 66}, {32, 66}, {32, 66}, {32, 67}, {32, 67}, {32, 68}, {32, 69}, {32, 69}, {32, 70}, {32, 70}, {32, 71}, {32, 71}, {32, 72}, {32, 72}, {32, 73}, {32, 73}, {32, 73}, {32, 74}, {32, 74}, {32, 75}, {33, 75}, {33, 75}, {33, 76}, {33, 76}, {33, 77}, {33, 77}, {33, 77}, {33, 78}, {33, 78}, {33, 78}, {33, 78}, {33, 78}, {33, 78}, {33, 79}, {33, 79}, {33, 79}, {33, 79}, {33, 80}, {33, 80}, {33, 80}, {33, 80}, {33, 80}, {33, 81}, {33, 81}, {33, 81}, {33, 81}, {33, 82}, {33, 82}, {33, 82}, {33, 82}, {33, 82}, {33, 83}, {33, 83}, {33, 83}, {33, 83}, {33, 83}, {33, 84}, {33, 84}, {33, 84}, {33, 84}, {33, 84}, {33, 85}, {33, 85}, {33, 85}, {34, 85}, {34, 85}, {34, 85}, {34, 85}, {35, 87}, {35, 87}, {35, 87}, {35, 87}, {35, 87}, {36, 87}, {36, 87}, {36, 87}, {36, 87}, {36, 87}, {37, 87}, {37, 87}, {37, 87}, {37, 87}, {37, 87}, {37, 87}, {38, 87}, {38, 88}, {38, 88}, {38, 88}, {38, 88}, {38, 88}, {39, 88}, {39, 88}, {39, 88}, {39, 88}, {39, 88}, {39, 89}, {39, 89}, {39, 89}, {40, 89}, {40, 89}, {40, 89}, {40, 89}, {40, 89}, {40, 89}, {41, 89}, {41, 90}, {41, 90}, {41, 90}, {41, 90}, {42, 90}, {42, 90}, {42, 90}, {42, 90}, {42, 90}, {42, 90}, {43, 90}, {43, 90}, {43, 90}, {43, 90}, {43, 90}, {44, 90}, {44, 90}, {44, 90}, {44, 90}, {45, 90}, {45, 90}, {45, 91}, {45, 91}, {45, 91}, {45, 91}, {46, 91}, {46, 91}, {46, 91}, {46, 91}, {46, 91}, {46, 91}, {47, 91}, {47, 91}, {47, 91}, {47, 91}, {48, 91}, {48, 91}, {48, 91}, {49, 91}, {49, 91}, {50, 91}, {50, 91}, {50, 91}, {50, 90}, {51, 90}, {51, 90}, {51, 90}, {51, 90}, {52, 90}, {52, 90}, {52, 90}, {52, 90}, {52, 90}, {53, 90}, {53, 90}, {53, 90}, {53, 90}, {54, 90}, {54, 90}, {54, 90}, {54, 90}, {55, 90}, {55, 90}, {55, 90}, {55, 90}, {56, 90}, {56, 90}, {57, 90}, {57, 90}, {57, 90}, {57, 90}, {57, 90}, {58, 90}, {58, 90}, {58, 89}, {58, 89}, {58, 89}, {59, 89}, {59, 89}, {59, 89}, {59, 89}, {60, 89}, {60, 89}, {60, 89}, {60, 89}, {60, 89}, {61, 89}, {61, 89}, {61, 89}, {61, 89}, {61, 89}, {62, 89}, {62, 89}, {62, 89}, {62, 89}, {62, 89}, {63, 89}, {63, 89}, {63, 89}, {63, 90}, {64, 90}, {64, 90}, {64, 90}, {64, 90}, {65, 90}, {65, 90}, {65, 90}, {65, 90}, {65, 90}, {66, 90}, {66, 90}, {66, 90}, {67, 90}, {67, 90}, {67, 90}, {67, 90}, {68, 90}, {68, 90}, {68, 90}, {68, 90}, {68, 90}, {69, 90}, {69, 90}, {69, 90}, {70, 90}, {70, 90}, {70, 90}, {71, 90}, {71, 90}, {72, 90}, {72, 90}, {73, 90}, {73, 90}, {74, 90}, {74, 90}, {74, 90}, {75, 90}, {75, 90}, {75, 90}, {76, 90}, {76, 90}, {77, 90}, {77, 90}, {78, 90}, {78, 90}, {79, 90}, {79, 90}, {80, 90}, {80, 89}, {80, 89}, {81, 89}, {81, 89}, {81, 89}, {82, 89}, {82, 89}, {82, 89}, {82, 89}, {82, 89}, {83, 89}, {83, 89}, {83, 89}, {84, 89}, {84, 89}, {84, 89}, {84, 89}, {85, 89}, {85, 89}, {85, 89}, {86, 89}, {86, 89}, {86, 89}, {87, 89}, {87, 89}, {87, 89}, {87, 89}, {88, 89}, {88, 89}, {88, 89}, {89, 89}, {89, 89}, {89, 89}, {89, 89}, {90, 89}, {90, 89}, {91, 89}, {91, 89}, {92, 89}, {92, 89}, {92, 90}, {92, 90}, {93, 90}, {93, 90}, {93, 90}, {93, 90}, {93, 90}, {94, 90}, {94, 90}, {94, 90}, {94, 90}, {94, 90}, {94, 90}, {95, 90}, {95, 90}, {95, 90}, {95, 90}, {96, 90}, {96, 90}, {96, 90}, {96, 90}, {96, 90}, {96, 90}, {97, 90}, {97, 90}, {97, 90}, {97, 90}, {97, 90}, {98, 90}, {98, 90}, {98, 90}, {98, 90}, {98, 90}, {98, 90}, {98, 90}, {98, 89}, {98, 88}, {98, 87}, {98, 86}, {98, 85}, {98, 85}, {98, 84}, {98, 84}, {98, 83}, {98, 83}, {98, 83}, {98, 83}, {98, 82}, {98, 82}, {98, 82}, {98, 81}, {98, 81}, {98, 81}, {98, 81}, {98, 80}, {98, 80}, {98, 80}, {98, 80}, {98, 79}, {98, 79}, {98, 79}, {98, 78}, {98, 78}, {98, 78}, {98, 78}, {98, 78}, {98, 77}, {98, 77}, {98, 77}, {98, 76}, {98, 76}, {98, 76}, {98, 75}, {98, 75}, {98, 74}, {98, 74}, {98, 74}, {98, 73}, {98, 73}, {98, 73}, {98, 73}, {98, 73}, {98, 73}, {98, 72}, {98, 72}, {98, 72}, {98, 71}, {98, 71}, {98, 71}, {98, 71}, {98, 71}, {97, 71}, {97, 71}, {97, 71}, {97, 71}, {96, 71}, {96, 71}, {96, 71}, {96, 71}, {96, 71}, {95, 71}, {95, 71}, {95, 71}, {95, 71}, {95, 71}, {94, 71}, {94, 71}, {94, 71}, {94, 71}, {94, 71}, {93, 71}, {93, 71}, {93, 71}, {93, 70}, {92, 70}, {92, 70}, {92, 70}, {92, 70}, {91, 70}, {91, 70}, {91, 70}, {91, 70}, {90, 70}, {90, 70}, {89, 70}, {89, 70}, {89, 70}, {88, 70}, {88, 70}, {88, 70}, {87, 70}, {87, 70}, {86, 70}, {86, 70}, {86, 70}, {85, 70}, {85, 70}, {84, 70}, {84, 70}, {84, 70}, {83, 70}, {83, 70}, {82, 70}, {82, 70}, {82, 70}, {81, 70}, {81, 70}, {80, 70}, {80, 70}, {80, 70}, {79, 70}, {79, 70}, {79, 70}, {79, 70}, {78, 70}, {78, 70}, {77, 70}, {77, 70}, {76, 70}, {76, 70}, {76, 70}, {76, 70}, {76, 71}, {75, 71}, {75, 71}, {75, 71}, {75, 71}, {74, 71}, {74, 71}, {74, 71}, {73, 71}, {73, 71}, {72, 71}, {72, 71}, {72, 71}, {72, 71}, {72, 71}, {71, 71}, {71, 71}, {71, 71}, {70, 71}, {70, 71}, {70, 71}, {70, 71}, {69, 71}, {69, 71}, {68, 71}, {68, 71}, {67, 71}, {67, 71}, {67, 71}, {67, 71}, {66, 71}, {66, 71}, {65, 71}, {65, 71}, {65, 71}, {64, 71}, {64, 71}, {63, 71}, {63, 71}, {63, 71}, {63, 71}, {62, 71}, {62, 71}, {62, 71}, {61, 71}, {61, 71}, {61, 71}, {60, 71}, {60, 71}, {60, 71}, {60, 71}, {59, 71}, {59, 71}, {59, 71}, {58, 71}, {58, 71}, {58, 71}, {58, 71}, {57, 71}, {57, 71}, {57, 71}, {57, 71}, {56, 71}, {56, 71}, {56, 71}, {56, 71}, {56, 71}, {55, 71}, {55, 71}, {55, 71}, {55, 71}, {55, 71}, {55, 71}, {54, 71}, {54, 71}, {54, 71}, {54, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 71}, {53, 70}, {53, 70}, {53, 70}, {53, 69}, {53, 69}, {53, 69}, {53, 69}, {53, 68}, {53, 68}, {53, 67}, {53, 67}, {53, 66}, {53, 66}, {53, 66}, {53, 65}, {53, 65}, {53, 64}, {53, 64}, {53, 64}, {53, 64}, {53, 63}, {53, 63}, {53, 62}, {53, 62}, {53, 62}, {53, 61}, {53, 61}, {53, 61}, {53, 60}, {53, 60}, {53, 60}, {53, 60}, {53, 59}, {53, 59}, {53, 59}, {53, 59}, {53, 59}, {53, 58}, {53, 58}, {53, 58}, {53, 58}, {53, 57}, {53, 57}, {53, 57}, {53, 57}, {53, 56}, {53, 56}, {53, 56}, {53, 55}, {53, 55}, {53, 55}, {53, 54}, {53, 54}, {53, 54}, {53, 53}, {53, 53}, {53, 52}, {53, 52}, {53, 52}, {53, 52}, {53, 52}, {53, 52}, {53, 52}, {53, 51}, {53, 51}, {53, 51}, {53, 51}, {53, 50}, {53, 50}, {53, 49}, {53, 49}, {53, 49}, {53, 49}, {53, 49}, {53, 49}, {54, 49}, {54, 49}, {54, 49}, {54, 49}, {55, 49}, {55, 49}, {55, 49}, {55, 49}, {55, 49}, {55, 49}, {56, 49}, {56, 49}, {56, 49}, {56, 49}, {56, 49}, {57, 49}, {57, 49}, {57, 49}, {57, 50}, {57, 50}, {58, 50}, {58, 50}, {58, 50}, {58, 50}, {59, 50}, {59, 50}, {59, 50}, {59, 50}, {60, 50}, {60, 50}, {60, 50}, {60, 50}, {61, 50}, {61, 50}, {61, 50}, {61, 50}, {62, 50}, {62, 50}, {62, 50}, {62, 50}, {63, 50}, {63, 50}, {63, 50}, {63, 50}, {63, 50}, {64, 50}, {64, 50}, {65, 50}, {65, 50}, {65, 50}, {65, 50}, {66, 50}, {66, 50}, {67, 50}, {67, 50}, {67, 50}, {68, 50}, {68, 50}, {69, 50}, {69, 50}, {69, 50}, {70, 50}, {70, 50}, {70, 50}, {71, 49}, {72, 49}, {72, 49}, {72, 49}, {73, 49}, {73, 49}, {74, 49}, {74, 49}, {74, 49}, {75, 49}, {75, 49}, {75, 49}, {76, 49}, {76, 49}, {77, 49}, {77, 49}, {77, 49}, {77, 48}, {77, 48}, {78, 48}, {78, 48}, {78, 48}, {78, 48}, {79, 48}, {79, 48}, {79, 48}, {79, 48}, {80, 48}, {80, 48}, {80, 48}, {81, 48}, {81, 48}, {81, 48}, {81, 48}, {82, 48}, {82, 48}, {82, 48}, {82, 48}, {83, 48}, {83, 48}, {83, 48}, {84, 48}, {84, 48}, {84, 48}, {85, 48}, {87, 48}};


    // std::vector<Punto> puntosReducidos2 = reducirPuntosAdaptativo(eliminarDuplicados(puntosOriginales), 8);
    // std::vector<Punto> puntosReducidos2 = filtrarPorCurvatura(eliminarDuplicados(puntosOriginales), 0.5);
    

    double umbralAngulo = 1.2; // Ajusta para mantener más o menos detalles
    std::vector<Punto> filtrados = filtrarPuntos(eliminarDuplicados(puntosOriginales), umbralAngulo);
    std::vector<Punto> suavizados = suavizarBezier(filtrados, 20);
    // std::vector<Punto> puntosReducidos3 = reducirPuntosAdaptativo(puntosOriginales, 9.0);
    // std::vector<Punto> puntosDouglas2;
    // DouglasPeucker(puntosOriginales, 0.7, puntosDouglas2);
    // // std::vector<Punto> puntosDouglas3;
    // // DouglasPeucker(puntosOriginales, 0.9, puntosDouglas3);
    //     int iteraciones = 20;
    // float alpha = 0.7; // Ajusta qué tan agresivo es el corte


    //  std::vector<Punto> puntosReducidos = suavizarTrayectoriaCornerCutting(puntosReducidos2, iteraciones, alpha);
    //  std::vector<Punto> filtrados = suavizarTrayectoriaBezier(filtrados2);
    // std::vector<Punto> puntosDouglas = suavizarTrayectoriaBezier(puntosDouglas2);
    // std::vector<Punto> puntosSinDuplicados = suavizarTrayectoriaBezier(puntosDouglas3);
    

    // Crear imágenes separadas
    cv::Mat imagenOriginal = cv::Mat::zeros(500, 500, CV_8UC3);
    cv::Mat imagenReducidos = cv::Mat::zeros(500, 500, CV_8UC3);
    // cv::Mat imagenDouglas = cv::Mat::zeros(500, 500, CV_8UC3);
    // cv::Mat imagenFiltrados = cv::Mat::zeros(500, 500, CV_8UC3);
    // cv::Mat imagenSinDuplicados = cv::Mat::zeros(500, 500, CV_8UC3);

    // Dibujar cada trayectoria en una imagen diferente
    dibujarTrayectoria(imagenOriginal, puntosOriginales, cv::Scalar(0, 0, 255), 2);      // Rojo (original)
    dibujarTrayectoria(imagenReducidos, suavizados, cv::Scalar(0, 255, 0), 2);      // Verde (reducción adaptativa)
    // dibujarTrayectoria(imagenDouglas, puntosDouglas2, cv::Scalar(0, 255, 255), 2);        // Amarillo (Douglas-Peucker)
    // dibujarTrayectoria(imagenFiltrados, puntosFiltrados, cv::Scalar(255, 255, 0), 2);    // Azul (Mediana Móvil)
    // dibujarTrayectoria(imagenSinDuplicados, puntosSinDuplicados, cv::Scalar(0, 255, 255), 2);  // Cyan (Eliminar duplicados)

    // Mostrar cada imagen en una ventana separada
    cv::imshow("Trayectoria Original", imagenOriginal);
    cv::imshow("Reducción 0.1", imagenReducidos);
    // cv::imshow("Douglas-Peucker 0.5", imagenDouglas);
    // cv::imshow("reduccion adaptativa 9", imagenFiltrados);
    // cv::imshow("Douglas-Peucker 0.9", imagenSinDuplicados);

    cv::waitKey(0); // Esperar hasta que se presione una tecla

    return 0;
}
