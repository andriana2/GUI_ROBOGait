#ifndef PROCESSCONTROLLER_H
#define PROCESSCONTROLLER_H

#include <rclcpp/rclcpp.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unistd.h>   // Para fork, execvp y sleep
#include <csignal>    // Para kill
#include <sys/wait.h> // Para waitpid

#include "utils.h"

class ProcessController
{
public:
    ProcessController();
    bool isNodeRunning(const std::string& node_name);
    void startProcess(const std::string &name, const std::string &command);
    void stopProcess(const std::string &name);
    void stopAllProcesses();
    void listProcesses() const;

private:
     std::unordered_map<std::string, pid_t> processMap;
};



#endif // PROCESSCONTROLLER_H