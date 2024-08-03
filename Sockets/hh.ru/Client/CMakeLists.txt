include(FetchContent)
cmake_minimum_required(VERSION 3.28)
project(Client)

set(CMAKE_CXX_STANDARD 26)

FetchContent_Declare(
        liburing4cpp
        GIT_REPOSITORY https://github.com/CarterLi/liburing4cpp.git
        GIT_TAG        async
)
FetchContent_MakeAvailable(liburing4cpp)

add_executable(Client main.cpp)

target_link_libraries(Client liburing4cpp)