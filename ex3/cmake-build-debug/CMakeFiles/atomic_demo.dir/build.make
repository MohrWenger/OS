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
CMAKE_SOURCE_DIR = /cs/usr/ellonet/SCHOOL/OS/ex3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/atomic_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/atomic_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/atomic_demo.dir/flags.make

CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.o: CMakeFiles/atomic_demo.dir/flags.make
CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.o: ../demos/atomicdemo/atomicdemo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.o -c /cs/usr/ellonet/SCHOOL/OS/ex3/demos/atomicdemo/atomicdemo.cpp

CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/SCHOOL/OS/ex3/demos/atomicdemo/atomicdemo.cpp > CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.i

CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/SCHOOL/OS/ex3/demos/atomicdemo/atomicdemo.cpp -o CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.s

# Object files for target atomic_demo
atomic_demo_OBJECTS = \
"CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.o"

# External object files for target atomic_demo
atomic_demo_EXTERNAL_OBJECTS =

atomic_demo: CMakeFiles/atomic_demo.dir/demos/atomicdemo/atomicdemo.cpp.o
atomic_demo: CMakeFiles/atomic_demo.dir/build.make
atomic_demo: CMakeFiles/atomic_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable atomic_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atomic_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/atomic_demo.dir/build: atomic_demo

.PHONY : CMakeFiles/atomic_demo.dir/build

CMakeFiles/atomic_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/atomic_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/atomic_demo.dir/clean

CMakeFiles/atomic_demo.dir/depend:
	cd /cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/ellonet/SCHOOL/OS/ex3 /cs/usr/ellonet/SCHOOL/OS/ex3 /cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug /cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug /cs/usr/ellonet/SCHOOL/OS/ex3/cmake-build-debug/CMakeFiles/atomic_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/atomic_demo.dir/depend
