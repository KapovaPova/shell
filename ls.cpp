//
// Created by kapovapova on 5/11/26.
//

#include "ls.h"
#include <filesystem>
#include <string>

std::string ls(const std::string& command) {
    bool show_hidden = command.find("-a") != std::string::npos;

    std::string result;
    for (const auto& file : std::filesystem::directory_iterator(path)) {
        std::string name = file.path().filename().string();
        if (!show_hidden && name[0] == '.') continue;
        result += name + '\n';
    }
    return result;
}
