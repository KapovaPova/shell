//
// Created by kapovapova on 5/11/26.
//

#ifndef SHELL_CD_H
#define SHELL_CD_H
#include <string>

extern std::string path;
extern std::string prev_path;

std::string cd(const std::string& command);

#endif //SHELL_CD_H
