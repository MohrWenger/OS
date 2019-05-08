cmake_minimum_required(VERSION 3.12)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(edited_client_testing MapReduceFramework.h MapReduceFramework.cpp MapReduceClient.h SampleClient_for_testing.cpp Barrier.h Barrier.cpp)
add_executable(client_testing MapReduceFramework.h MapReduceFramework.cpp MapReduceClient.h SampleClient.cpp Barrier.h Barrier.cpp)
add_executable(atomic_demo demos/atomicdemo/atomicdemo.cpp)
add_executable(barrier_demo demos/barrierdemo/barrierdemo.cpp demos/barrierdemo/Barrier1.cpp demos/barrierdemo/Barrier1.h)
add_executable(reut_test Count.cpp MapReduceFramework.h MapReduceFramework.cpp MapReduceClient.h Barrier.h Barrier.cpp MapReduceClient.h)


add_executable(ex3 MapReduceFramework.h MapReduceFramework.cpp MapReduceClient.h SampleClient.cpp Barrier.h Barrier.cpp)
