cmake_minimum_required(VERSION 3.28)
project(test)

set(CMAKE_CXX_STANDARD 23)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
set(TensorFlow_BUILD_DIR "/usr/lib/")
set(TensorFlow_C_LIBRARY "/usr/lib/libtensorflow_cc.so.2.16.1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(TensorFlow)
#set(TensorFlow_INCLUDE_DIR  "${TensorFlow_INCLUDE_DIR}")

message("PATH: " ${TensorFlow_C_LIBRARY})
include_directories(${TensorFlow_INCLUDE_DIR} ${TensorFlow_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=${TensorFlow_ABI}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=${TensorFlow_ABI}" )
#TensorFlow_REQUIRE_C_LIBRARY()
#TensorFlow_REQUIRE_SOURCE()

include_directories($ENV{TENSORFLOW_BUILD_DIR}/includes/)
add_executable(test src/main.cpp
        src/simple_model.hpp
        src/simple_model.cpp)

target_include_directories(test PRIVATE TensorFlow_DEP)
target_link_libraries(test PRIVATE TensorFlow_DEP)
target_link_libraries(test PUBLIC ${TensorFlow_C_LIBRARY})
