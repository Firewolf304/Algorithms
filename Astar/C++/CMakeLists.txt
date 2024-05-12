cmake_minimum_required(VERSION 3.28)
project(Astar)

set(CMAKE_CXX_STANDARD 26)

find_package(fmt)
add_executable(Astar src/main.cpp
        src/astar_algos.hpp)
target_link_libraries(Astar fmt)
