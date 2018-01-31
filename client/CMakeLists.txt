cmake_minimum_required(VERSION 3.8)
project(Chess)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c defs.h init.c bitboard.c)
add_executable(Chess ${SOURCE_FILES})