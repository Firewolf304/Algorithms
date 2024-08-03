cmake_minimum_required(VERSION 3.28)
project(toml)


set(CMAKE_CXX_STANDARD 26)
# vcpkg install tomlplusplus
find_package(PkgConfig REQUIRED)
pkg_check_modules(tomlplusplus REQUIRED IMPORTED_TARGET tomlplusplus)

add_executable(toml main.cpp)
target_link_libraries(toml PkgConfig::tomlplusplus)
