//
// Created by kapovapova on 5/11/26.
//

#include "execute.h"
#include "ls.h"
#include "pwd.h"
#include "cd.h"

std::string execute(const std::string& command, const std::string& input) {
    if (command.substr(0, 2) == "ls") return ls(command);
    if (command == "pwd") return pwd();
    if (command.substr(0, 2) == "cd") return cd(command);
    return "Unknown command: " + command + '!';
}
