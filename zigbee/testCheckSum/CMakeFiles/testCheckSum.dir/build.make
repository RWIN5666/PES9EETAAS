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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum

# Include any dependencies generated for this target.
include CMakeFiles/testCheckSum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testCheckSum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testCheckSum.dir/flags.make

CMakeFiles/testCheckSum.dir/main/main.c.o: CMakeFiles/testCheckSum.dir/flags.make
CMakeFiles/testCheckSum.dir/main/main.c.o: main/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/testCheckSum.dir/main/main.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/testCheckSum.dir/main/main.c.o   -c /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum/main/main.c

CMakeFiles/testCheckSum.dir/main/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testCheckSum.dir/main/main.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum/main/main.c > CMakeFiles/testCheckSum.dir/main/main.c.i

CMakeFiles/testCheckSum.dir/main/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testCheckSum.dir/main/main.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum/main/main.c -o CMakeFiles/testCheckSum.dir/main/main.c.s

CMakeFiles/testCheckSum.dir/main/main.c.o.requires:
.PHONY : CMakeFiles/testCheckSum.dir/main/main.c.o.requires

CMakeFiles/testCheckSum.dir/main/main.c.o.provides: CMakeFiles/testCheckSum.dir/main/main.c.o.requires
	$(MAKE) -f CMakeFiles/testCheckSum.dir/build.make CMakeFiles/testCheckSum.dir/main/main.c.o.provides.build
.PHONY : CMakeFiles/testCheckSum.dir/main/main.c.o.provides

CMakeFiles/testCheckSum.dir/main/main.c.o.provides.build: CMakeFiles/testCheckSum.dir/main/main.c.o

# Object files for target testCheckSum
testCheckSum_OBJECTS = \
"CMakeFiles/testCheckSum.dir/main/main.c.o"

# External object files for target testCheckSum
testCheckSum_EXTERNAL_OBJECTS =

testCheckSum: CMakeFiles/testCheckSum.dir/main/main.c.o
testCheckSum: src/zigbee/libzigbee.so
testCheckSum: CMakeFiles/testCheckSum.dir/build.make
testCheckSum: CMakeFiles/testCheckSum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable testCheckSum"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testCheckSum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testCheckSum.dir/build: testCheckSum
.PHONY : CMakeFiles/testCheckSum.dir/build

CMakeFiles/testCheckSum.dir/requires: CMakeFiles/testCheckSum.dir/main/main.c.o.requires
.PHONY : CMakeFiles/testCheckSum.dir/requires

CMakeFiles/testCheckSum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testCheckSum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testCheckSum.dir/clean

CMakeFiles/testCheckSum.dir/depend:
	cd /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum /home/erwin/Documents/PRE/PES9EETAAS/zigbee/testCheckSum/CMakeFiles/testCheckSum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testCheckSum.dir/depend

