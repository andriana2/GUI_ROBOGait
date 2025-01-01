#include "../include/utils.h"

std::string headerToString(Header header)
{
    switch (header)
    {
    case MSG:
        return "MSG";
    case REQUEST_MSG:
        return "REQUEST_MSG";
    case IMG:
        return "IMG";
    case REQUEST_IMG:
        return "REQUEST_IMG";
    default:
        return "UNKNOWN";
    }
}

Header stringToHeader(const std::string &str)
{
    if (str == "MSG")
        return MSG;
    if (str == "REQUEST_MSG")
        return REQUEST_MSG;
    if (str == "IMG")
        return IMG;
    if (str == "REQUEST_IMG")
        return REQUEST_IMG;
    throw std::invalid_argument("Invalid Header string: " + str);
}

// Funciones para Target
std::string targetToString(Target target)
{
    switch (target)
    {
    case Joystick_Position:
        return "Joystick_Position";
    case Map_SLAM:
        return "Map_SLAM";
    case Robot_Position_Pixel:
        return "Robot_Position_Pixel";
    case Img_Map_SLAM:
        return "Img_Map_SLAM";
    case Save_Map:
        return "Save_Map";
    default:
        return "UNKNOWN";
    }
}

Target stringToTarget(const std::string &str)
{
    if (str == "Joystick_Position")
        return Joystick_Position;
    if (str == "Map_SLAM")
        return Map_SLAM;
    if (str == "Robot_Position_Pixel")
        return Robot_Position_Pixel;
    if (str == "Img_Map_SLAM")
        return Img_Map_SLAM;
    if (str == "Save_Map")
        return Save_Map;
    throw std::invalid_argument("Invalid Target string: " + str);
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

std::vector<std::string> executeCommand(const std::string &command)
{
    std::vector<std::string> results;
    std::array<char, 128> buffer;
    std::string result;

    // Abrir un pipe para ejecutar el comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("Error al abrir el pipe para ejecutar el comando.");
    }

    // Leer la salida del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    // Dividir la salida en líneas y añadirlas al vector
    std::istringstream stream(result);
    std::string line;
    while (std::getline(stream, line))
    {
        if (!line.empty())
        { // Ignorar líneas vacías
            results.push_back(line);
        }
    }

    return results;
}

std::vector<std::string> splitJson(const std::string& input) {
    std::vector<std::string> jsons;
    std::string buffer;
    int braceCounter = 0;

    for (char c : input) {
        buffer += c;

        if (c == '{') {
            braceCounter++;
        } else if (c == '}') {
            braceCounter--;
        }

        // When a complete JSON object is found
        if (braceCounter == 0 && !buffer.empty()) {
            jsons.push_back(buffer);
            buffer.clear(); // Clear the buffer for the next JSON
        }
    }

    if (braceCounter != 0) {
        throw std::runtime_error("The input contains an incomplete JSON.");
    }

    return jsons;
}

// Función para convertir datos binarios a texto hexadecimal
// std::string toHex(const char* data, std::size_t length)
// {
//     static const char* hexDigits = "0123456789ABCDEF";
//     std::string hex;
//     hex.reserve(length * 2);

//     for (std::size_t i = 0; i < length; ++i)
//     {
//         unsigned char byte = static_cast<unsigned char>(data[i]);
//         hex.push_back(hexDigits[byte >> 4]);
//         hex.push_back(hexDigits[byte & 0x0F]);
//     }

//     return hex;
// }


