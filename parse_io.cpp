//
// Created by kapovapova on 5/11/26.
//

#include "parse_io.h"
#include <iostream>
#include "split.h"
#include <vector>
#include <fstream>

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