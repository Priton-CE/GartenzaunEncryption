cmake_minimum_required(VERSION 3.13)
project(gartenzaun)
set(CMAKE_C_STANDARD 23)

set(SOURCE_FILES
    src/main.c
    src/gartenzaun.h
    src/gartenzaun.c
)

add_executable(gartenzaun ${SOURCE_FILES})
