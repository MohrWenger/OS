cmake_minimum_required(VERSION 3.12)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 main.cpp)
add_executable(ex3_atomic_demo demos/atomicdemo/atomicdemo.cpp)