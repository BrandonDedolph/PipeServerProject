# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /opt/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brandon/CLionProjects/PipeServerProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brandon/CLionProjects/PipeServerProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CSCI311P3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CSCI311P3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CSCI311P3.dir/flags.make

CMakeFiles/CSCI311P3.dir/interface.c.o: CMakeFiles/CSCI311P3.dir/flags.make
CMakeFiles/CSCI311P3.dir/interface.c.o: ../interface.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brandon/CLionProjects/PipeServerProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CSCI311P3.dir/interface.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSCI311P3.dir/interface.c.o   -c /home/brandon/CLionProjects/PipeServerProject/interface.c

CMakeFiles/CSCI311P3.dir/interface.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSCI311P3.dir/interface.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brandon/CLionProjects/PipeServerProject/interface.c > CMakeFiles/CSCI311P3.dir/interface.c.i

CMakeFiles/CSCI311P3.dir/interface.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSCI311P3.dir/interface.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brandon/CLionProjects/PipeServerProject/interface.c -o CMakeFiles/CSCI311P3.dir/interface.c.s

CMakeFiles/CSCI311P3.dir/interface.c.o.requires:

.PHONY : CMakeFiles/CSCI311P3.dir/interface.c.o.requires

CMakeFiles/CSCI311P3.dir/interface.c.o.provides: CMakeFiles/CSCI311P3.dir/interface.c.o.requires
	$(MAKE) -f CMakeFiles/CSCI311P3.dir/build.make CMakeFiles/CSCI311P3.dir/interface.c.o.provides.build
.PHONY : CMakeFiles/CSCI311P3.dir/interface.c.o.provides

CMakeFiles/CSCI311P3.dir/interface.c.o.provides.build: CMakeFiles/CSCI311P3.dir/interface.c.o


CMakeFiles/CSCI311P3.dir/server.c.o: CMakeFiles/CSCI311P3.dir/flags.make
CMakeFiles/CSCI311P3.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brandon/CLionProjects/PipeServerProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CSCI311P3.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSCI311P3.dir/server.c.o   -c /home/brandon/CLionProjects/PipeServerProject/server.c

CMakeFiles/CSCI311P3.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSCI311P3.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brandon/CLionProjects/PipeServerProject/server.c > CMakeFiles/CSCI311P3.dir/server.c.i

CMakeFiles/CSCI311P3.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSCI311P3.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brandon/CLionProjects/PipeServerProject/server.c -o CMakeFiles/CSCI311P3.dir/server.c.s

CMakeFiles/CSCI311P3.dir/server.c.o.requires:

.PHONY : CMakeFiles/CSCI311P3.dir/server.c.o.requires

CMakeFiles/CSCI311P3.dir/server.c.o.provides: CMakeFiles/CSCI311P3.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/CSCI311P3.dir/build.make CMakeFiles/CSCI311P3.dir/server.c.o.provides.build
.PHONY : CMakeFiles/CSCI311P3.dir/server.c.o.provides

CMakeFiles/CSCI311P3.dir/server.c.o.provides.build: CMakeFiles/CSCI311P3.dir/server.c.o


# Object files for target CSCI311P3
CSCI311P3_OBJECTS = \
"CMakeFiles/CSCI311P3.dir/interface.c.o" \
"CMakeFiles/CSCI311P3.dir/server.c.o"

# External object files for target CSCI311P3
CSCI311P3_EXTERNAL_OBJECTS =

CSCI311P3: CMakeFiles/CSCI311P3.dir/interface.c.o
CSCI311P3: CMakeFiles/CSCI311P3.dir/server.c.o
CSCI311P3: CMakeFiles/CSCI311P3.dir/build.make
CSCI311P3: CMakeFiles/CSCI311P3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brandon/CLionProjects/PipeServerProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable CSCI311P3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CSCI311P3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CSCI311P3.dir/build: CSCI311P3

.PHONY : CMakeFiles/CSCI311P3.dir/build

CMakeFiles/CSCI311P3.dir/requires: CMakeFiles/CSCI311P3.dir/interface.c.o.requires
CMakeFiles/CSCI311P3.dir/requires: CMakeFiles/CSCI311P3.dir/server.c.o.requires

.PHONY : CMakeFiles/CSCI311P3.dir/requires

CMakeFiles/CSCI311P3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CSCI311P3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CSCI311P3.dir/clean

CMakeFiles/CSCI311P3.dir/depend:
	cd /home/brandon/CLionProjects/PipeServerProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brandon/CLionProjects/PipeServerProject /home/brandon/CLionProjects/PipeServerProject /home/brandon/CLionProjects/PipeServerProject/cmake-build-debug /home/brandon/CLionProjects/PipeServerProject/cmake-build-debug /home/brandon/CLionProjects/PipeServerProject/cmake-build-debug/CMakeFiles/CSCI311P3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CSCI311P3.dir/depend

