# cmake_minimum_required(VERSION <specify CMake version here>)
project(Network_Programming C)

set(CMAKE_C_STANDARD 99)

#add_executable(Chess_Engine engine/main.c engine/init.c engine/defs.h engine/bitboards.c engine/hashkeys.c engine/board.c engine/data.c engine/attack.c engine/io.c engine/movegen.c engine/validate.c engine/makemove.c engine/perft.c server/server.c)

add_executable(server server/server.c)

target_link_libraries(server ws2_32)

add_executable(client client/client.c)

target_link_libraries(client ws2_32)