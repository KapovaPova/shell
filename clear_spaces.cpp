//
// Created by kapovapova on 5/11/26.
//

#include "clear_spaces.h"

void clear_spaces(std::vector<std::string>& commands) {
    for (std::string& command : commands) {
        size_t first = command.find_first_not_of(" \t\n\r");
        size_t last = command.find_last_not_of(" \t\n\r");
        if (first == std::string::npos || last == std::string::npos) {
            command.clear();
            continue;
        }
        command = command.substr(first, last - first + 1);
    }

    for (auto it = commands.begin(); it != commands.end();) {
        if (it->empty()) {
            it = commands.erase(it);
        } else {
            it++;
        }
    }
}