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

std::vector<std::string> executeCommand(const std::string& command) {
    std::vector<std::string> results;
    std::array<char, 128> buffer;
    std::string result;

    // Abrir un pipe para ejecutar el comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Error al abrir el pipe para ejecutar el comando.");
    }

    // Leer la salida del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Dividir la salida en líneas y añadirlas al vector
    std::istringstream stream(result);
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty()) { // Ignorar líneas vacías
            results.push_back(line);
        }
    }

    return results;
}
