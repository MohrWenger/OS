cmake_minimum_required(VERSION 3.12)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2_sleep_test1 uthreads.h uthreads.cpp Thread.h sleeping_threads_list.cpp sleeping_threads_list.h SleepTest.cpp)
add_executable(ex2_sleep_test2 uthreads.h uthreads.cpp Thread.h sleeping_threads_list.cpp sleeping_threads_list.h SleepTest2.cpp)
add_executable(ex2_test1 uthreads.h uthreads.cpp Thread.h sleeping_threads_list.cpp sleeping_threads_list.h test1.cpp)
add_executable(ex2_test2 uthreads.h uthreads.cpp Thread.h sleeping_threads_list.cpp sleeping_threads_list.h test2.cpp)
add_executable(ex2_test3 uthreads.h uthreads.cpp Thread.h sleeping_threads_list.cpp sleeping_threads_list.h test3.cpp)
add_executable(ex2_test4 uthreads.h uthreads.cpp Thread.h sleeping_threads_list.cpp sleeping_threads_list.h test4.cpp)
