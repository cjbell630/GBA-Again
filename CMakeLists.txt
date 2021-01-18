cmake_minimum_required(VERSION 3.17)
project(GBA_Again C)

set(CMAKE_C_STANDARD 11)

add_executable(GBA_Again
        first/source/first.c
        second/source/second.c
        multiple_code_files/source/main.c
        keys/source/key_demo.c
        )
