cmake_minimum_required(VERSION 3.6)
project(Game_of_Life)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c src/png_reader.c src/png_reader.h src/png_writer.c src/png_writer.h src/grid.c src/grid.h
        src/neighbourhoods.c src/neighbourhoods.h src/simulator.c src/simulator.h)
add_executable(Game_of_Life ${SOURCE_FILES})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(Game_of_Life ${PNG_LIBRARY})
