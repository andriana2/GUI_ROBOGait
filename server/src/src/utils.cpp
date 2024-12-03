#include "../include/utils.h"

std::string get_info_message(Info_Message const &info)
{
    switch (info)
    {
    case 1:
        return ("Lista_mapa");
        break;
    case 2:
        return ("Position_joystick");
        break;
    case 3:
        return ("Guardar_mapa");
        break;
    default:
        throw std::invalid_argument("no existe ese info en get_info_message");
        break;
    }
}
Info_Message get_info_message_enum(std::string const &info)
{
    if (info == "Lista_mapa")
        return Lista_mapa;
    else if (info == "Position_joystick")
        return Position_joystick;
    else if (info == "Guardar_mapa")
        return Guardar_mapa;

    else
        throw std::invalid_argument("no existe ese info en Info_Message get_info_message_enum");
}

void getValuePositionJoystick(const std::string &input, float &linear, float &angular)
{
    // Usamos un stringstream para dividir la cadena
    std::stringstream ss(input);
    std::string segmento;

    // Variables para almacenar los valores
    linear = 0.0f;
    angular = 0.0f;

    // Extraemos "Linear: valor" y "Angular: valor"
    while (std::getline(ss, segmento, ','))
    {
        size_t pos = segmento.find(':');
        if (pos != std::string::npos)
        {
            std::string key = segmento.substr(0, pos);
            float value = std::stof(segmento.substr(pos + 1));

            if (key.find("Linear") != std::string::npos)
            {
                linear = value;
            }
            else if (key.find("Angular") != std::string::npos)
            {
                angular = value;
            }
        }
    }
    std::cout << "Linear: " << linear << ", Angular: " << angular << std::endl;
}

void pri1(std::string const &msg)
{
    std::cout << msg << std::endl;
}
