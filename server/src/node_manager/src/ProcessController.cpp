#include "../include/ProcessController.h"

ProcessController::ProcessController() {}

bool ProcessController::isNodeRunning(const std::string &node_name)
{
    auto node = rclcpp::Node::make_shared("node_checker");
    auto node_names = node->get_node_names();

    for (const auto &name : node_names)
    {
        if (name == node_name)
        {
            return true;
        }
    }
    return false;
}

void ProcessController::startProcess(const std::string &name, const std::string &command)
{
    // Verifica si el nodo ya está corriendo
    if (isNodeRunning(name) && (command.find("ros2 run") != std::string::npos))
    {
        std::cout << "ProcessController: El nodo \"" << name << "\" ya está en ejecución.\n";
        return;
    }

    // Verifica si el proceso ya está en ejecución
    if (processMap.find(name) != processMap.end())
    {
        std::cout << "ProcessController: El proceso \"" << name << "\" ya está en ejecución.\n";
        return;
    }

    // Divide la cadena en argumentos
    std::vector<std::string> args = splitCommand(command);

    // Convierte los argumentos en un arreglo de punteros a const char*
    std::vector<const char *> cArgs;
    for (const auto &arg : args)
    {
        cArgs.push_back(arg.c_str());
    }
    cArgs.push_back(nullptr); // Termina con nullptr como requiere execvp

    // Crea un proceso hijo y ejecuta el comando
    pid_t pid = fork();
    if (pid == 0)
    {
        // Proceso hijo
        execvp(cArgs[0], const_cast<char *const *>(cArgs.data()));
        std::cerr << "ProcessController: Error al ejecutar el comando: " << command << std::endl;
        perror("execvp"); // Imprime el error específico de execvp
        std::cerr << "Ejecutando comando: " << command << std::endl;
        _exit(1);
    }
    else if (pid < 0)
    {
        // Error al crear el proceso
        std::cerr << "ProcessController: Error al crear el proceso \"" << name << "\".\n";
    }
    else
    {
        // Proceso padre
        processMap[name] = pid;
        std::cout << "ProcessController: Proceso \"" << name << "\" iniciado con PID: " << pid << std::endl;

        // Esperar a que el proceso termine pero solo en el caso de guardar mapa
        if (name == NAME_MAP_SAVER_CLI)
        {
            int status;
            waitpid(pid, &status, 0);
            std::cout << "ProcessController: Proceso \"" << name << "\" finalizado con código de salida: " << WEXITSTATUS(status) << std::endl;
            stopProcess(name);
        }
    }
}

// Función para detener un proceso
void ProcessController::stopProcess(const std::string &name)
{
    auto it = processMap.find(name);
    if (it != processMap.end())
    {
        pid_t pid = it->second;
        kill(pid, SIGINT); // Enviar señal para detener el proceso

        // Esperar a que el proceso termine
        int status;
        while (waitpid(pid, &status, 0) == -1)
        {
            if (errno != EINTR)
            {
                std::cerr << "ProcessController: Error al esperar el proceso \"" << name << "\".\n";
                break;
            }
        }

        // Verificar si el proceso sigue en ejecución y usar SIGKILL como respaldo
        if (kill(pid, 0) == 0)
        {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
        }

        std::cout << "ProcessController: Proceso \"" << name << "\" detenido (PID: " << pid << ").\n";

        // Eliminar el proceso del mapa
        processMap.erase(it);
    }
    else
    {
        std::cout << "ProcessController: No se encontró el proceso \"" << name << "\" en ejecución.\n";
    }
}

// Función para detener todos los procesos
// void ProcessController::stopAllProcesses()
// {
//     for (const auto &[name, pid] : processMap)
//     {
//         pri1("Estoy en stopAllProcesses");
//         pri1(name);
//         pri1(std::to_string(pid));
//         // Enviar SIGTERM para un cierre ordenado
//         kill(pid, SIGINT);
//         int status;
//         waitpid(pid, &status, WNOHANG);

//         // Verificar si el proceso sigue en ejecución y usar SIGKILL como respaldo
//         if (kill(pid, 0) == 0) {
//             std::cout << "Proceso \"" << name << "\" aún está en ejecución. Enviando SIGKILL." << std::endl;
//             kill(pid, SIGKILL);
//             waitpid(pid, &status, 0);
//         }

//         // Verificar el estado del proceso después de la terminación
//         if (WIFEXITED(status)) {
//             std::cout << "Proceso \"" << name << "\" terminado normalmente con código de salida: " << WEXITSTATUS(status) << std::endl;
//         } else if (WIFSIGNALED(status)) {
//             std::cout << "Proceso \"" << name << "\" terminado por una señal: " << WTERMSIG(status) << std::endl;
//         } else if (WIFSTOPPED(status)) {
//             std::cout << "Proceso \"" << name << "\" detenido por una señal: " << WSTOPSIG(status) << std::endl;
//         }

//         std::cout << "ProcessController: Proceso \"" << name << "\" detenido (PID: " << pid << ").\n";
//     }

//     processMap.clear();
// }

// void ProcessController::stopAllProcesses()
// {
//     for (auto it = processMap.begin(); it != processMap.end();)
//     {
//         const std::string &name = it->first;
//         pid_t pid = it->second;

//         std::cout << "Deteniendo proceso: " << name << " (PID: " << pid << ")" << std::endl;

//         // Intentar una terminación ordenada con SIGTERM
//         kill(pid, SIGINT);

//         int status;
//         int wait_result = waitpid(pid, &status, 0);

//         // Si el proceso sigue corriendo después de SIGTERM, forzar con SIGKILL
//         if (wait_result == 0)
//         {
//             std::cout << "Proceso \"" << name << "\" aún en ejecución, enviando SIGKILL..." << std::endl;
//             kill(pid, SIGKILL);
//             waitpid(pid, &status, 0); // Esperamos su terminación
//         }

//         // Comprobar cómo terminó el proceso
//         if (WIFEXITED(status))
//         {
//             std::cout << "Proceso \"" << name << "\" terminó normalmente con código: " << WEXITSTATUS(status) << std::endl;
//         }
//         else if (WIFSIGNALED(status))
//         {
//             std::cout << "Proceso \"" << name << "\" fue terminado por la señal: " << WTERMSIG(status) << std::endl;
//         }

//         // Borrar el proceso de la lista después de confirmarlo muerto
//         it = processMap.erase(it);
//     }

//     std::cout << "Todos los procesos han sido detenidos." << std::endl;
// }

void ProcessController::stopAllProcesses()
{
    for (auto it = processMap.begin(); it != processMap.end();)
    {
        const std::string &name = it->first;
        pid_t pid = it->second;

        std::cout << "Deteniendo proceso: " << name << " (PID: " << pid << ")" << std::endl;

        // Intentar una terminación ordenada con SIGTERM
        if (name == NAME_START_ROBOT)
            kill(pid, SIGINT);
        else
            kill(pid, SIGTERM);

        int status;
        int wait_result = waitpid(pid, &status, WNOHANG);

        // Si el proceso sigue corriendo después de SIGTERM, forzar con SIGKILL
        if (wait_result == 0)
        {
            std::cout << "Proceso \"" << name << "\" aún en ejecución, esperando..." << std::endl;

            // Esperamos unos segundos para ver si se cierra solo
            for (int i = 0; i < 5; i++)
            {
                sleep(1);
                wait_result = waitpid(pid, &status, WNOHANG);
                if (wait_result != 0)
                    break; // El proceso terminó, salir del bucle
            }

            if (wait_result == 0)
            {
                std::cout << "Proceso \"" << name << "\" aún en ejecución, enviando SIGKILL..." << std::endl;

                // Si el proceso generó hijos, eliminarlos también
                kill(-pid, SIGKILL);      // Mata el grupo de procesos
                sleep(1);                 // Pequeño delay para evitar inconsistencias
                waitpid(pid, &status, 0); // Bloqueamos hasta que muera
            }
        }

        // Comprobar cómo terminó el proceso
        if (WIFEXITED(status))
        {
            std::cout << "Proceso \"" << name << "\" terminó normalmente con código: " << WEXITSTATUS(status) << std::endl;
        }
        else if (WIFSIGNALED(status))
        {
            std::cout << "Proceso \"" << name << "\" fue terminado por la señal: " << WTERMSIG(status) << std::endl;
        }

        // Borrar el proceso de la lista después de confirmarlo muerto
        it = processMap.erase(it);
    }

    std::cout << "Todos los procesos han sido detenidos." << std::endl;
}

// Función para verificar los procesos en ejecución
void ProcessController::listProcesses() const
{
    if (processMap.empty())
    {
        std::cout << "ProcessController: No hay procesos en ejecución.\n";
    }
    else
    {
        std::cout << "ProcessController: Procesos en ejecución:\n";
        for (const auto &[name, pid] : processMap)
        {
            std::cout << "  - " << name << " (PID: " << pid << ")\n";
        }
    }
}