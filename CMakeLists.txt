cmake_minimum_required(VERSION 4.2)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c
        main.c
        sort.c
        sort.h)

add_executable(tests
        tests.c
        sort.c
        sort.h)
