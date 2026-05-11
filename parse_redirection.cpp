//
// Created by kapovapova on 5/11/26.
//

#include "parse_redirection.h"
#include <vector>
#include "split.h"
#include "parse_io.h"
#include <iostream>
#include "read_from_file.h"
#include "execute.h"
#include "write_to_file.h"

void parse_redirection(const std::string& command) {
    std::vector<std::string> commands = split(command, "|");
    std::string buff = "";

    for (const std::string& sub_command : commands) {
        std::string cmd, input, output;
        parse_io(sub_command, cmd, input, output);
        if (cmd.empty()) {
            std::cerr << "Failed to get the command!" << std::endl;
            return;
        }

        std::string current_input;
        if (!input.empty()) {
            current_input = read_from_file(input);
        } else {
            current_input = buff;
        }

        std::string result = execute(cmd, current_input);

        if (!output.empty()) {
            write_to_file(output, result);
            buff = "";
        } else {
            buff = result;
        }
    }

    if (!buff.empty()) {
        std::cout << buff << std::endl;
    }
}