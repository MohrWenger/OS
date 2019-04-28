cmake_minimum_required(VERSION 3.12)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(client_testing MapReduceFramework.h MapReduceFramework.cpp MapReduceClient.h SampleClient_for_testing.cpp)
add_executable(atomic_demo demos/atomicdemo/atomicdemo.cpp)


add_executable(ex3 MapReduceFramework.h MapReduceFramework.cpp MapReduceClient.h SampleClient.cpp)
