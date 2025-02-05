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
    case Request_Map_SLAM:
        return "Request_Map_SLAM";
    case Robot_Position_Pixel:
        return "Robot_Position_Pixel";
    case Img_Map_SLAM:
        return "Img_Map_SLAM";
    case Img_Map_Path:
        return "Img_Map_Path";
    case Save_Map:
        return "Save_Map";
    case State_Remote_Controlled:
        return "State_Remote_Controlled";
    case State_Menu:
        return "State_Menu";
    case Map_Name:
        return "Map_Name";
    case Map_Info_Image_Size:
        return "Map_Info_Image_Size";
    case Change_Map_Name:
        return "Change_Map_Name";
    case Delete_Map:
        return "Delete_Map";
    case Img_Map_Select:
        return "Img_Map_Select";
    case Goal_Pose:
        return "Goal_Pose";
    case Waypoint_Follower:
        return "Waypoint_Follower";
    default:
        return "UNKNOWN";
    }
}

Target stringToTarget(const std::string &str)
{
    if (str == "Joystick_Position")
        return Joystick_Position;
    if (str == "Request_Map_SLAM")
        return Request_Map_SLAM;
    if (str == "Robot_Position_Pixel")
        return Robot_Position_Pixel;
    if (str == "Img_Map_SLAM")
        return Img_Map_SLAM;
    if (str == "Img_Map_Path")
        return Img_Map_Path;
    if (str == "Save_Map")
        return Save_Map;
    if (str == "State_Remote_Controlled")
        return State_Remote_Controlled;
    if (str == "State_Menu")
        return State_Menu;
    if (str == "Map_Name")
        return Map_Name;
    if (str == "Map_Info_Image_Size")
        return Map_Info_Image_Size;
    if (str == "Change_Map_Name")
        return Change_Map_Name;
    if (str == "Delete_Map")
        return Delete_Map;
    if (str == "Img_Map_Select")
        return Img_Map_Select;
    if (str == "Goal_Pose")
        return Goal_Pose;
    if (str == "Waypoint_Follower")
        return Waypoint_Follower;

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
            pri1(leftoverBuffer);
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

std::string replaceSpaces(const std::string &name)
{
    std::string modifiedName = name;
    for (auto &c : modifiedName)
    {
        if (c == ' ')
        {
            c = '#'; // Use a special character, such as '#'
        }
    }
    return modifiedName;
}

// Function to restore spaces from the special delimiter
std::string restoreSpaces(const std::string &name)
{
    std::string originalName = name;
    for (auto &c : originalName)
    {
        if (c == '#')
        {
            c = ' '; // Restore spaces
        }
    }
    return originalName;
}

std::vector<std::string> getMapName(std::string const &path)
{
    std::vector<std::string> map_name;
    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        if (file.is_regular_file() && file.path().extension() == ".pgm")
        {
            // Utilizamos .stem() para obtener el nombre del archivo sin extensión
            std::string name_without_extension = file.path().stem().string();
            name_without_extension = restoreSpaces(name_without_extension);
            pri1(name_without_extension);
            map_name.push_back(name_without_extension);
        }
    }
    return map_name;
}

void getImageSize(std::string const &path, int &width_output, int &height_output)
{
    std::ifstream file(path); // Cambia "imagen.pgm" por la ruta de tu archivo
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        exit(1);
    }

    std::string line;
    int width = 0, height = 0;

    // Leer primera línea (formato P5)
    std::getline(file, line);

    // Leer segunda línea (dimensiones)
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> width >> height;
    }

    std::cout << "Ancho: " << width << ", Alto: " << height << std::endl;

    width_output = width;
    height_output = height;
    file.close();
}

std::vector<std::string> splitCommand(const std::string &command)
{
    std::vector<std::string> args;
    std::istringstream stream(command);
    std::string arg;
    while (stream >> arg)
    {
        args.push_back(arg);
    }
    return args;
}

RealPositionMeters getRealPosition(const std::string &path_yaml, const int x_pixel, const int y_pixel)
{
    RealPositionMeters real_position;
    try
    {
        YAML::Node config = YAML::LoadFile(path_yaml);

        // Obtener la resolución
        float resolution = config["resolution"].as<float>();
        std::cout << "Resolución: " << resolution << std::endl;

        // Obtener los valores de origen
        auto origin = config["origin"];
        float origin_x = origin[0].as<float>();
        float origin_y = origin[1].as<float>();
        std::cout << "Origen X: " << origin_x << ", Origen Y: " << origin_y << std::endl;

        real_position.x = x_pixel * resolution + origin_x;
        real_position.y = y_pixel * resolution + origin_y;
        std::cout << "Real X: " << real_position.x << ", Real Y: " << real_position.y << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
    }
    return real_position;
}
