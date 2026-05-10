#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void clear_spaces(std::vector<std::string>& commands) {
    for (std::string& command : commands) {
        size_t first = command.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
            command.clear();
            continue;
        }
        size_t last = command.find_last_not_of(" \t\n\r");
        command = command.substr(first, (last - first + 1));
    }
}

void clear_void(std::vector<std::string>& commands) {
    for (auto it = commands.begin(); it != commands.end();) {
        if (it->empty()) {
            it = commands.erase(it);
        } else {
            it++;
        }
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
    clear_void(result);

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
                std::cerr << "No file specified to read from!" << std::endl;
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
                std::cerr << "No file specified to write to!" << std::endl;
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

std::string read_from_file(const std::string& filename) {
    std::string result;

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            result += line;
            result += '\n';
        }
        file.close();

        return result;
    } else {
        std::cerr << "Couldn't open file: " << filename << '!' << std::endl;
        return "";
    }

}

void write_to_file(const std::string& filename, const std::string& data) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << data;
        file.close();
    } else {
        std::cerr << "Couldn't open file: " << filename << '!' << std::endl;
        return;
    }
}

std::string execute(const std::string& command, const std::string& input) {
    if (command.find("echo") == 0) {
        return (command.length() > 5) ? command.substr(5) : "";
    }
    if (command == "rev") {
        std::string s = input;
        std::reverse(s.begin(), s.end());
        return s;
    }
    if (command == "upper") {
        std::string s = input;
        for (char &c : s) c = toupper(c);
        return s;
    }
    return "Unknown command: " + command;
}

void parse_redirection(const std::string& command) {
    std::vector<std::string> commands = split(command, "|");
    std::string buff = "";

    for (const std::string& sub_command : commands) {
        std::string cmd, input, output;
        parse_io(sub_command, cmd, input, output);
        if (cmd.empty()) {
            std::cerr << "Failed to get the command!" << std::endl;
            return;
        }

        std::string current_input;
        if (!input.empty()) {
            current_input = read_from_file(input);
        } else {
            current_input = buff;
        }

        std::string result = execute(cmd, current_input);

        if (!output.empty()) {
            write_to_file(output, result);
            buff = "";
        } else {
            buff = result;
        }
    }

    if (!buff.empty()) {
        std::cout << buff << std::endl;
    }
}

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
