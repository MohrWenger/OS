# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\ClionProjects\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\ClionProjects\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ClionProjects\OS\ex3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ClionProjects\OS\ex3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3.dir/flags.make

CMakeFiles/ex3.dir/MapReduceFramework.cpp.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/MapReduceFramework.cpp.obj: ../MapReduceFramework.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\OS\ex3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex3.dir/MapReduceFramework.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ex3.dir\MapReduceFramework.cpp.obj -c D:\ClionProjects\OS\ex3\MapReduceFramework.cpp

CMakeFiles/ex3.dir/MapReduceFramework.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex3.dir/MapReduceFramework.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\OS\ex3\MapReduceFramework.cpp > CMakeFiles\ex3.dir\MapReduceFramework.cpp.i

CMakeFiles/ex3.dir/MapReduceFramework.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex3.dir/MapReduceFramework.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\OS\ex3\MapReduceFramework.cpp -o CMakeFiles\ex3.dir\MapReduceFramework.cpp.s

CMakeFiles/ex3.dir/SampleClient.cpp.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/SampleClient.cpp.obj: ../SampleClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\OS\ex3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex3.dir/SampleClient.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ex3.dir\SampleClient.cpp.obj -c D:\ClionProjects\OS\ex3\SampleClient.cpp

CMakeFiles/ex3.dir/SampleClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex3.dir/SampleClient.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\OS\ex3\SampleClient.cpp > CMakeFiles\ex3.dir\SampleClient.cpp.i

CMakeFiles/ex3.dir/SampleClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex3.dir/SampleClient.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\OS\ex3\SampleClient.cpp -o CMakeFiles\ex3.dir\SampleClient.cpp.s

CMakeFiles/ex3.dir/Barrier.cpp.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/Barrier.cpp.obj: ../Barrier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\OS\ex3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ex3.dir/Barrier.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ex3.dir\Barrier.cpp.obj -c D:\ClionProjects\OS\ex3\Barrier.cpp

CMakeFiles/ex3.dir/Barrier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex3.dir/Barrier.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\OS\ex3\Barrier.cpp > CMakeFiles\ex3.dir\Barrier.cpp.i

CMakeFiles/ex3.dir/Barrier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex3.dir/Barrier.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\OS\ex3\Barrier.cpp -o CMakeFiles\ex3.dir\Barrier.cpp.s

# Object files for target ex3
ex3_OBJECTS = \
"CMakeFiles/ex3.dir/MapReduceFramework.cpp.obj" \
"CMakeFiles/ex3.dir/SampleClient.cpp.obj" \
"CMakeFiles/ex3.dir/Barrier.cpp.obj"

# External object files for target ex3
ex3_EXTERNAL_OBJECTS =

ex3.exe: CMakeFiles/ex3.dir/MapReduceFramework.cpp.obj
ex3.exe: CMakeFiles/ex3.dir/SampleClient.cpp.obj
ex3.exe: CMakeFiles/ex3.dir/Barrier.cpp.obj
ex3.exe: CMakeFiles/ex3.dir/build.make
ex3.exe: CMakeFiles/ex3.dir/linklibs.rsp
ex3.exe: CMakeFiles/ex3.dir/objects1.rsp
ex3.exe: CMakeFiles/ex3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ClionProjects\OS\ex3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ex3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ex3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3.dir/build: ex3.exe

.PHONY : CMakeFiles/ex3.dir/build

CMakeFiles/ex3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ex3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ex3.dir/clean

CMakeFiles/ex3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ClionProjects\OS\ex3 D:\ClionProjects\OS\ex3 D:\ClionProjects\OS\ex3\cmake-build-debug D:\ClionProjects\OS\ex3\cmake-build-debug D:\ClionProjects\OS\ex3\cmake-build-debug\CMakeFiles\ex3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex3.dir/depend

