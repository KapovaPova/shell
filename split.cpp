//
// Created by kapovapova on 5/11/26.
//

#include "split.h"
#include "clear_spaces.h"

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