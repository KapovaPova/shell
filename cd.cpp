//
// Created by kapovapova on 5/11/26.
//

#include "cd.h"
#include <filesystem>
#include "split.h"

std::string cd(const std::string& command) {
    auto args = split(command, " ");

    if (args.size() < 2) {
        return "cd: missing argument";
    }


    const std::string& target = args[1];

    std::filesystem::path new_path;
    if (target == "~")
        new_path = std::filesystem::path(getenv("HOME"));
    else if (target == "-")
        new_path = std::filesystem::path(prev_path);
    else
        new_path = std::filesystem::weakly_canonical(std::filesystem::path(path) / target);

    if (!std::filesystem::is_directory(new_path))
        return "cd: no such directory: " + target;

    prev_path = path;
    path = new_path.string();
    return "";
}
