cmake_minimum_required(VERSION 3.6)
project(Game_of_Life)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic") # nie działa?

set(SOURCE_FILES
        src/main.c
        src/grid.c src/grid.h
        src/bmp_reader.c src/bmp_reader.h
        src/neighbourhoods.c src/neighbourhoods.h
        src/png_reader.c src/png_reader.h
        src/png_writer.c src/png_writer.h
        src/simulator.c src/simulator.h
        )
add_executable(life ${SOURCE_FILES})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(life ${PNG_LIBRARY})

find_package (Threads)
target_link_libraries (life ${CMAKE_THREAD_LIBS_INIT})
