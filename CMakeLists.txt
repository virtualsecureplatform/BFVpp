cmake_minimum_required(VERSION 3.9)
project(bfv++ CXX)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-march=native -O3 -std=c++17 -g")

add_subdirectory(thirdparties/randen)
add_subdirectory(thirdparties/spqlios)

if(ENABLE_TEST)
    add_subdirectory(test)
endif()