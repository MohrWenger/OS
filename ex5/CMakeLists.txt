cmake_minimum_required(VERSION 3.12)
project(ex5)

set(CMAKE_CXX_STANDARD 14)

#add_executable(ex5 prints.h FileAppClient.cpp FileAppServer.cpp)
add_executable(ex5_server prints.h FileAppServer.cpp)
#add_executable(ex5_client prints.h FileAppClient.cpp)