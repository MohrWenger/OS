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
CMAKE_SOURCE_DIR = /cs/usr/mohr/Desktop/Studies/OS/ex4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex4_like_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex4_like_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex4_like_example.dir/flags.make

CMakeFiles/ex4_like_example.dir/main.cpp.o: CMakeFiles/ex4_like_example.dir/flags.make
CMakeFiles/ex4_like_example.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex4_like_example.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex4_like_example.dir/main.cpp.o -c /cs/usr/mohr/Desktop/Studies/OS/ex4/main.cpp

CMakeFiles/ex4_like_example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4_like_example.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/mohr/Desktop/Studies/OS/ex4/main.cpp > CMakeFiles/ex4_like_example.dir/main.cpp.i

CMakeFiles/ex4_like_example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4_like_example.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/mohr/Desktop/Studies/OS/ex4/main.cpp -o CMakeFiles/ex4_like_example.dir/main.cpp.s

CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.o: CMakeFiles/ex4_like_example.dir/flags.make
CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.o: ../VirtualMemory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.o -c /cs/usr/mohr/Desktop/Studies/OS/ex4/VirtualMemory.cpp

CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/mohr/Desktop/Studies/OS/ex4/VirtualMemory.cpp > CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.i

CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/mohr/Desktop/Studies/OS/ex4/VirtualMemory.cpp -o CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.s

CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.o: CMakeFiles/ex4_like_example.dir/flags.make
CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.o: ../PhysicalMemory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.o -c /cs/usr/mohr/Desktop/Studies/OS/ex4/PhysicalMemory.cpp

CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/mohr/Desktop/Studies/OS/ex4/PhysicalMemory.cpp > CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.i

CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/mohr/Desktop/Studies/OS/ex4/PhysicalMemory.cpp -o CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.s

# Object files for target ex4_like_example
ex4_like_example_OBJECTS = \
"CMakeFiles/ex4_like_example.dir/main.cpp.o" \
"CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.o" \
"CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.o"

# External object files for target ex4_like_example
ex4_like_example_EXTERNAL_OBJECTS =

ex4_like_example: CMakeFiles/ex4_like_example.dir/main.cpp.o
ex4_like_example: CMakeFiles/ex4_like_example.dir/VirtualMemory.cpp.o
ex4_like_example: CMakeFiles/ex4_like_example.dir/PhysicalMemory.cpp.o
ex4_like_example: CMakeFiles/ex4_like_example.dir/build.make
ex4_like_example: CMakeFiles/ex4_like_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ex4_like_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex4_like_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex4_like_example.dir/build: ex4_like_example

.PHONY : CMakeFiles/ex4_like_example.dir/build

CMakeFiles/ex4_like_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex4_like_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex4_like_example.dir/clean

CMakeFiles/ex4_like_example.dir/depend:
	cd /cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/mohr/Desktop/Studies/OS/ex4 /cs/usr/mohr/Desktop/Studies/OS/ex4 /cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug /cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug /cs/usr/mohr/Desktop/Studies/OS/ex4/cmake-build-debug/CMakeFiles/ex4_like_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex4_like_example.dir/depend

