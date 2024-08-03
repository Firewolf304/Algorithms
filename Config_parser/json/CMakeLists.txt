cmake_minimum_required(VERSION 3.28)
project(json)

set(CMAKE_CXX_STANDARD 26)

find_package(nlohmann_json)

add_executable(json main.cpp)

target_link_libraries(nlohmann_json::nlohmann_json)