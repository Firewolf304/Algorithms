cmake_minimum_required(VERSION 3.28)
project(k_means CUDA)

set(CMAKE_CUDA_STANDARD 23)
find_package(fmt)
#find_package(GTest REQUIRED)
add_executable(k_means src/main.cu
        include/local.hpp
        include/cpu.hxx
        include/libs.hpp
        src/objects/cpu.cxx
        include/points/point.hxx
        src/objects/point.cpp
)
target_link_libraries(k_means
        PRIVATE
        fmt::fmt
)
set_target_properties(k_means PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
