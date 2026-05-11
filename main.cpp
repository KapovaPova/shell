#include <iostream>
#include "split.h"
#include "parse_redirection.h"
#include <string>
#include <filesystem>

std::string path = std::filesystem::current_path().string();
std::string username = "kapovapova";
std::string system_name = "archlinux";

int main() {
    while (true) {
        std::string command;
        std::cout << '[' << username << '@' << system_name << ' ' << path << "]$ ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        std::vector<std::string> commands = split(command, ";");
        for (const std::string& sub_command : commands) {
            parse_redirection(sub_command);
        }
    }

    return 0;
}
