# cmake_minimum_required(VERSION <specify CMake version here>)
#project(Network_Programming C)
#
#set(CMAKE_C_STANDARD 99)
#
#add_executable(Chess_Engine engine/wincheck.c engine/main.c engine/init.c engine/defs.h engine/bitboards.c engine/hashkeys.c engine/board.c engine/data.c engine/attack.c engine/io.c engine/movegen.c engine/validate.c engine/makemove.c engine/perft.c)

cmake_minimum_required(VERSION 3.9)
project(chess C)

#if(MINGW)
#    set(CMAKE_RC_COMPILER_INIT windres)
#    ENABLE_LANGUAGE(RC)
#    SET(CMAKE_RC_COMPILE_OBJECT
#            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
#endif(MINGW)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/gui/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_MIXER REQUIRED)

add_executable(chess
        gui/mainGUI.c
        gui/draw.c
        gui/draw.h
        gui/move.c
        gui/move.h
        engine/init.c
        engine/defs.h
        engine/bitboards.c
        engine/hashkeys.c
        engine/board.c
        engine/data.c
        engine/attack.c
        engine/io.c
        engine/movegen.c
        engine/validate.c
        engine/makemove.c
        engine/perft.c
        engine/wincheck.c
        gui/init.h gui/initSDL.c)


include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        )
target_link_libraries(chess ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        )

#add_executable(Chess_Engine
#        engine/main.c
#        engine/init.c
#        engine/defs.h
#        engine/bitboards.c
#        engine/hashkeys.c
#        engine/board.c
#        engine/data.c
#        engine/attack.c
#        engine/io.c
#        engine/movegen.c
#        engine/validate.c
#        engine/makemove.c
#        engine/perft.c
#        engine/wincheck.c)

