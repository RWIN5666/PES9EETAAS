# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/erwin/Documents/PRE/PES9EETAAS/theMain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erwin/Documents/PRE/PES9EETAAS/theMain

# Include any dependencies generated for this target.
include CMakeFiles/42main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/42main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/42main.dir/flags.make

CMakeFiles/42main.dir/main/main.c.o: CMakeFiles/42main.dir/flags.make
CMakeFiles/42main.dir/main/main.c.o: main/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PRE/PES9EETAAS/theMain/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/42main.dir/main/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/42main.dir/main/main.c.o   -c /home/erwin/Documents/PRE/PES9EETAAS/theMain/main/main.c

CMakeFiles/42main.dir/main/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/42main.dir/main/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PRE/PES9EETAAS/theMain/main/main.c > CMakeFiles/42main.dir/main/main.c.i

CMakeFiles/42main.dir/main/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/42main.dir/main/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PRE/PES9EETAAS/theMain/main/main.c -o CMakeFiles/42main.dir/main/main.c.s

CMakeFiles/42main.dir/main/main.c.o.requires:
.PHONY : CMakeFiles/42main.dir/main/main.c.o.requires

CMakeFiles/42main.dir/main/main.c.o.provides: CMakeFiles/42main.dir/main/main.c.o.requires
	$(MAKE) -f CMakeFiles/42main.dir/build.make CMakeFiles/42main.dir/main/main.c.o.provides.build
.PHONY : CMakeFiles/42main.dir/main/main.c.o.provides

CMakeFiles/42main.dir/main/main.c.o.provides.build: CMakeFiles/42main.dir/main/main.c.o

# Object files for target 42main
42main_OBJECTS = \
"CMakeFiles/42main.dir/main/main.c.o"

# External object files for target 42main
42main_EXTERNAL_OBJECTS =

42main: CMakeFiles/42main.dir/main/main.c.o
42main: CMakeFiles/42main.dir/build.make
42main: src/serial0/libserial0.so
42main: src/zigbee/libzigbee.so
42main: src/dessinterminal/libdessinterminal.so
42main: src/hexLib/libhexLib.so
42main: CMakeFiles/42main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable 42main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/42main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/42main.dir/build: 42main
.PHONY : CMakeFiles/42main.dir/build

CMakeFiles/42main.dir/requires: CMakeFiles/42main.dir/main/main.c.o.requires
.PHONY : CMakeFiles/42main.dir/requires

CMakeFiles/42main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/42main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/42main.dir/clean

CMakeFiles/42main.dir/depend:
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erwin/Documents/PRE/PES9EETAAS/theMain /home/erwin/Documents/PRE/PES9EETAAS/theMain /home/erwin/Documents/PRE/PES9EETAAS/theMain /home/erwin/Documents/PRE/PES9EETAAS/theMain /home/erwin/Documents/PRE/PES9EETAAS/theMain/CMakeFiles/42main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/42main.dir/depend

