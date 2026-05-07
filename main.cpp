#include <iostream>
#include <string>

int execute(const std::string& command) {
    std::cout << "'" << command << "'" << std::endl;
    return 0;
}

int main() {
    while (true) {
        std::string command;
        std::cout << "[kapovapova@archlinux ~]$ ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        //делим на токены
        std::string tokens = "|<>&;";

        size_t pos = command.find_first_of(tokens);
        size_t last_pos = 0;

        while (pos != std::string::npos) {

            //проверяем на токены
            switch (command[pos]) {
                case '|':
                    execute(command.substr(last_pos, pos - last_pos));
                    break;
            }

            last_pos = pos + 1;
            pos = command.find_first_of(tokens, pos + 1);
        }

        execute(command.substr(last_pos));
    }

    return 0;
}
