//
// Created by kapovapova on 5/11/26.
//

#include "ls.h"
#include <filesystem>
#include <string>

std::string ls() {
    std::string result = "";
    for (const auto& file : std::filesystem::directory_iterator(path)) {
        result += file.path().filename().string() + '\n';
    }
    return result;
}