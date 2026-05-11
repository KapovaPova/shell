//
// Created by kapovapova on 5/11/26.
//

#include "cd.h"
#include <filesystem>
#include "split.h"

std::string cd(const std::string& command) {
    if (command.substr(0, 3) != "cd ") return "cd: missing argument!";

    std::string target = split(command, " ")[1];

    std::filesystem::path new_path = std::filesystem::weakly_canonical(std::filesystem::path(path) / target);
    if (std::filesystem::is_directory(new_path)) {
        path = new_path.string();
        return "";
    }

    return "cd: no such directory!";
}