//
// Created by kapovapova on 5/11/26.
//

#include "execute.h"
#include <algorithm>
#include <iostream>

std::string execute(const std::string& command, const std::string& input) {
    if (command.find("echo") == 0) {
        return (command.length() > 5) ? command.substr(5) : "";
    }
    if (command == "rev") {
        std::string s = input;
        std::reverse(s.begin(), s.end());
        return s;
    }
    if (command == "upper") {
        std::string s = input;
        for (char &c : s) c = toupper(c);
        return s;
    }
    return "Unknown command: " + command;
}