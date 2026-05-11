#include <iostream>
#include "split.h"
#include "parse_redirection.h"

int main() {
    while (true) {
        std::string command;
        std::cout << "[kapovapova@archlinux ~]$ ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        std::vector<std::string> commands = split(command, ";");
        for (const std::string& sub_command : commands) {
            parse_redirection(sub_command);
        }
    }

    return 0;
}
