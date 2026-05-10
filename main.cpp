#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void clear_spaces(std::vector<std::string>& commands) {
    for (std::string& command : commands) {
        command.erase(0, command.find_first_not_of(" \t\n\r"));
        command.erase(command.find_last_not_of(" \t\n\r") + 1);
    }
}

std::vector<std::string> split(const std::string& command, const std::string& dividers) {
    std::vector<std::string> result;

    size_t pos = command.find_first_of(dividers);
    size_t last_pos = 0;
    while (pos != std::string::npos) {
        result.push_back(command.substr(last_pos, pos - last_pos));
        last_pos = pos + 1;
        pos = command.find_first_of(dividers, pos + 1);
    }
    result.push_back(command.substr(last_pos));

    clear_spaces(result);

    return result;
}

void parse_io(const std::string& command, std::string& cmd, std::string& input, std::string& output) {
    //делим по пробелам для последующей обработки < и >
    std::vector<std::string> tokens = split(command, " ");

    for (auto it = tokens.begin(); it != tokens.end(); ) {
        if (*it == "<") {
            if (std::next(it) != tokens.end()) {
                input = *(std::next(it));
                it = tokens.erase(it);
                it = tokens.erase(it);
            } else {
                it = tokens.erase(it);
            }
        } else if (*it == ">" || *it == ">>") {
            if (std::next(it) != tokens.end()) {
                output = *(std::next(it));
                if (*it == ">") {
                    std::ofstream tmp(output);
                    tmp.close();
                }
                it = tokens.erase(it);
                it = tokens.erase(it);
            } else {
                it = tokens.erase(it);
            }
        } else {
            it++;
        }
    }

    for (const std::string& rest : tokens) {
        if (!cmd.empty()) cmd += ' ';
        cmd += rest;
    }
}

int main() {
    while (true) {
        std::string command;
        std::cout << "[kapovapova@archlinux ~]$ ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        std::vector<std::string> level1 = split(command, ";");
        for (const std::string& lvl1_command : level1) {

            std::vector<std::string> level2 = split(lvl1_command, "|");
            for (const std::string& lvl2_command : level2) {

                std::string cmd, input, output;
                parse_io(lvl2_command, cmd, input, output);

                std::cout << "command: '" << cmd << "', input: '" << input << "', output: '" << output << "'" << std::endl;
            }
        }
    }

    return 0;
}
