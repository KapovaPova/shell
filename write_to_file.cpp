//
// Created by kapovapova on 5/11/26.
//

#include "write_to_file.h"
#include <fstream>
#include <iostream>

void write_to_file(const std::string& filename, const std::string& data) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << data;
        file.close();
        return;
    }

    std::cerr << "Couldn't open file: " << filename << '!' << std::endl;
}