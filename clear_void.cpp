//
// Created by kapovapova on 5/11/26.
//

#include "clear_void.h"

void clear_void(std::vector<std::string>& commands) {
    for (auto it = commands.begin(); it != commands.end();) {
        if (it->empty()) {
            it = commands.erase(it);
        } else {
            it++;
        }
    }
}