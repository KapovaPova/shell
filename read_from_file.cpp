//
// Created by kapovapova on 5/11/26.
//

#include "read_from_file.h"
#include <fstream>
#include <iostream>

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
    }

    std::cerr << "Couldn't open file: " << filename << '!' << std::endl;
    return "";
}