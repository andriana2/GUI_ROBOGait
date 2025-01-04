#include "../include/utils.h"
#include <boost/asio.hpp>
#include <boost/beast/core/detail/base64.hpp>


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
    case State_Remote_Controlled:
        return "";
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
    if (str == "State_Remote_Controlled")
        return State_Remote_Controlled;
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

std::vector<std::string> splitJson(const std::string &input)
{
    static std::string leftoverBuffer; // Almacena datos incompletos entre llamadas
    std::vector<std::string> jsons;
    std::string buffer = leftoverBuffer + input; // Combina el buffer previo con la nueva entrada
    leftoverBuffer.clear();                      // Limpia el buffer estático para llenarlo después si sobra algo

    int braceCounter = 0;

    for (char c : buffer)
    {
        leftoverBuffer += c;
        if (c == '{')
            braceCounter++;
        else if (c == '}')
            braceCounter--;
        // Cuando se encuentra un objeto JSON completo
        if (braceCounter == 0 && !leftoverBuffer.empty())
        {
            jsons.push_back(leftoverBuffer);
            leftoverBuffer.clear(); // Limpia el buffer para el siguiente JSON
        }
    }
    // Si sobra información incompleta, se guarda en el buffer estático
    if (braceCounter != 0)
        leftoverBuffer = buffer;
    return jsons;
}

std::string toBase64(const char *data, size_t length)
{
    std::string base64Str;
    base64Str.resize(boost::beast::detail::base64::encoded_size(length));

    boost::beast::detail::base64::encode(base64Str.data(), data, length);
    return base64Str;
}
