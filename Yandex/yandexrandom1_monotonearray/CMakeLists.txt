message(STATUS "Selected " $ENV{CMAKE_BUILD_NAME})
cmake_minimum_required(VERSION 3.30.8)
project($ENV{CMAKE_PROJECTNAME_ENV})

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

include(cmake/Options.cmake)
include(cmake/Vcpkg.cmake)
include(cmake/LinkerSettings.cmake)
include(cmake/LocalSet.cmake)

# Standard settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# nvim/vscode clangd helper
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/Packages.cmake)
add_executable(${PROJECT_NAME} src/main.cpp)
include(cmake/Targets.cmake)

# Add tests

include(CTest)

message(STATUS "BUILD_TESTING value: ${BUILD_TESTING}")
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()