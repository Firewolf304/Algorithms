include(FetchContent)
cmake_minimum_required(VERSION 3.28)
project(Server)

set(CMAKE_CXX_STANDARD 26)

FetchContent_Declare(
        liburing4cpp
        GIT_REPOSITORY https://github.com/CarterLi/liburing4cpp.git
        GIT_TAG        async
)
FetchContent_MakeAvailable(liburing4cpp)

add_executable(Server main.cpp)

target_link_libraries(Server liburing4cpp)