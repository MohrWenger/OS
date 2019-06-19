cmake_minimum_required(VERSION 3.12)
project(ex5)

set(CMAKE_CXX_STANDARD 14)
add_executable(ex5 prints.h FileAppServer.cpp FileAppClient.cpp main.cpp FileAppServer.h FileAppClient.h)