# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/APP/jetbrains/clion/2018.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/local/APP/jetbrains/clion/2018.2.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cs/usr/ellonet/SCHOOL/OS/ex4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex4_SimpleTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex4_SimpleTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex4_SimpleTest.dir/flags.make

CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.o: CMakeFiles/ex4_SimpleTest.dir/flags.make
CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.o: ../SimpleTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.o -c /cs/usr/ellonet/SCHOOL/OS/ex4/SimpleTest.cpp

CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/SCHOOL/OS/ex4/SimpleTest.cpp > CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.i

CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/SCHOOL/OS/ex4/SimpleTest.cpp -o CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.s

CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.o: CMakeFiles/ex4_SimpleTest.dir/flags.make
CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.o: ../VirtualMemory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.o -c /cs/usr/ellonet/SCHOOL/OS/ex4/VirtualMemory.cpp

CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/SCHOOL/OS/ex4/VirtualMemory.cpp > CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.i

CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/SCHOOL/OS/ex4/VirtualMemory.cpp -o CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.s

CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.o: CMakeFiles/ex4_SimpleTest.dir/flags.make
CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.o: ../PhysicalMemory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.o -c /cs/usr/ellonet/SCHOOL/OS/ex4/PhysicalMemory.cpp

CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/SCHOOL/OS/ex4/PhysicalMemory.cpp > CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.i

CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/SCHOOL/OS/ex4/PhysicalMemory.cpp -o CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.s

# Object files for target ex4_SimpleTest
ex4_SimpleTest_OBJECTS = \
"CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.o" \
"CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.o" \
"CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.o"

# External object files for target ex4_SimpleTest
ex4_SimpleTest_EXTERNAL_OBJECTS =

ex4_SimpleTest: CMakeFiles/ex4_SimpleTest.dir/SimpleTest.cpp.o
ex4_SimpleTest: CMakeFiles/ex4_SimpleTest.dir/VirtualMemory.cpp.o
ex4_SimpleTest: CMakeFiles/ex4_SimpleTest.dir/PhysicalMemory.cpp.o
ex4_SimpleTest: CMakeFiles/ex4_SimpleTest.dir/build.make
ex4_SimpleTest: CMakeFiles/ex4_SimpleTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ex4_SimpleTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex4_SimpleTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex4_SimpleTest.dir/build: ex4_SimpleTest

.PHONY : CMakeFiles/ex4_SimpleTest.dir/build

CMakeFiles/ex4_SimpleTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex4_SimpleTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex4_SimpleTest.dir/clean

CMakeFiles/ex4_SimpleTest.dir/depend:
	cd /cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/ellonet/SCHOOL/OS/ex4 /cs/usr/ellonet/SCHOOL/OS/ex4 /cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug /cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug /cs/usr/ellonet/SCHOOL/OS/ex4/cmake-build-debug/CMakeFiles/ex4_SimpleTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex4_SimpleTest.dir/depend
