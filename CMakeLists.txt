cmake_minimum_required(VERSION 4.2)
project(shell)

set(CMAKE_CXX_STANDARD 26)

add_executable(shell main.cpp
        clear_spaces.cpp
        clear_spaces.h
        split.cpp
        split.h
        parse_io.cpp
        parse_io.h
        read_from_file.cpp
        read_from_file.h
        write_to_file.cpp
        write_to_file.h
        execute.cpp
        execute.h
        parse_redirection.cpp
        parse_redirection.h
        ls.cpp
        ls.h
        pwd.cpp
        pwd.h
        cd.cpp
        cd.h)

target_link_libraries(shell readline)