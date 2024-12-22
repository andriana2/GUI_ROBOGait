#include <cmath>
#include <iostream>

double getYawFromQuaternion()
{
    // Extraer componentes del cuaternión

    double t1_rotation_x = 0.0000005;
    double t1_rotation_y = -0.003;
    double t1_rotation_z = -0.00168;
    double t1_rotation_w = 0.9999999;

    double t2_rotation_x = -0.0000008;
    double t2_rotation_y = 0.003;
    double t2_rotation_z = 0.0081;
    double t2_rotation_w = 0.999999;
    double rotation_x = t1_rotation_w * t2_rotation_x + t1_rotation_x * t2_rotation_w + t1_rotation_y * t2_rotation_z - t1_rotation_z * t2_rotation_y;
    double rotation_y = t1_rotation_w * t2_rotation_y - t1_rotation_x * t2_rotation_z + t1_rotation_y * t2_rotation_w + t1_rotation_z * t2_rotation_x;
    double rotation_z = t1_rotation_w * t2_rotation_z + t1_rotation_x * t2_rotation_y - t1_rotation_y * t2_rotation_x + t1_rotation_z * t2_rotation_w;
    double rotation_w = t1_rotation_w * t2_rotation_w - t1_rotation_x * t2_rotation_x - t1_rotation_y * t2_rotation_y - t1_rotation_z * t2_rotation_z;

    // Calcular yaw (ángulo alrededor del eje Z)
    double siny_cosp = 2.0 * (rotation_w * rotation_z + rotation_x * rotation_y);
    double cosy_cosp = 1.0 - 2.0 * (rotation_y * rotation_y + rotation_z * rotation_z);
    return std::atan2(siny_cosp, cosy_cosp); // Retorna el ángulo en radianes
}

int main()
{
    std::cout << getYawFromQuaternion() << std::endl;
    return 0;
}