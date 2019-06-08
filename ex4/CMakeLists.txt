cmake_minimum_required(VERSION 3.12)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex4_SimpleTest_old SimpleTest.cpp VirtualMemory_old.cpp VirtualMemory_old.h
        MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_SimpleTestDebug SimpleTestDebugging.cpp VirtualMemory_old.cpp VirtualMemory_old.h MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_our_main main.cpp VirtualMemory_old.cpp VirtualMemory_old.h MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_like_example main.cpp VirtualMemory_old.cpp VirtualMemory_old.h ConstantsTest.h PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_evyaTest_old FlowExampleSimulation.cpp VirtualMemory_old.cpp VirtualMemory_old.h
        MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h)


add_executable(ex4_evyaTest FlowExampleSimulation.cpp VirtualMemory.cpp VirtualMemory.h MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_SimpleTest SimpleTest.cpp VirtualMemory.cpp VirtualMemory.h MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_testerTest tester.cpp VirtualMemory.cpp VirtualMemory.h MemoryConstants.h
        PhysicalMemory.cpp PhysicalMemory.h)
add_executable(ex4_randomTest randomTest.cpp VirtualMemory.cpp VirtualMemory.h MemoryConstants.h
        PhysicalMemory.cpp PhysicalMemory.h)
