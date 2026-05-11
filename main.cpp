#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include "split.h"
#include "parse_redirection.h"
#include <string>
#include <filesystem>

std::string path = std::filesystem::current_path().string();
std::string username = "kapovapova";
std::string system_name = "archlinux";

int main() {
    while (true) {
        std::string text = std::string("[") + username + "@" + system_name + " " + path + "]$ ";

        char* input = readline(text.c_str());

        if (input == nullptr) break;

        std::string command(input);
        add_history(input);
        free(input);

        if (command == "exit") break;

        std::vector<std::string> commands = split(command, ";");
        for (const std::string& sub_command : commands) {
            parse_redirection(sub_command);
        }
    }

    return 0;
}