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
CMAKE_SOURCE_DIR = /home/erwin/Documents/PRE/PES9EETAAS/theMain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erwin/Documents/PRE/PES9EETAAS/theMain

# Include any dependencies generated for this target.
include src/serial0/CMakeFiles/serial0.dir/depend.make

# Include the progress variables for this target.
include src/serial0/CMakeFiles/serial0.dir/progress.make

# Include the compile flags for this target's objects.
include src/serial0/CMakeFiles/serial0.dir/flags.make

src/serial0/CMakeFiles/serial0.dir/serial0.c.o: src/serial0/CMakeFiles/serial0.dir/flags.make
src/serial0/CMakeFiles/serial0.dir/serial0.c.o: src/serial0/serial0.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PRE/PES9EETAAS/theMain/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/serial0/CMakeFiles/serial0.dir/serial0.c.o"
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/serial0.dir/serial0.c.o   -c /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0/serial0.c

src/serial0/CMakeFiles/serial0.dir/serial0.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serial0.dir/serial0.c.i"
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0/serial0.c > CMakeFiles/serial0.dir/serial0.c.i

src/serial0/CMakeFiles/serial0.dir/serial0.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serial0.dir/serial0.c.s"
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0/serial0.c -o CMakeFiles/serial0.dir/serial0.c.s

src/serial0/CMakeFiles/serial0.dir/serial0.c.o.requires:
.PHONY : src/serial0/CMakeFiles/serial0.dir/serial0.c.o.requires

src/serial0/CMakeFiles/serial0.dir/serial0.c.o.provides: src/serial0/CMakeFiles/serial0.dir/serial0.c.o.requires
	$(MAKE) -f src/serial0/CMakeFiles/serial0.dir/build.make src/serial0/CMakeFiles/serial0.dir/serial0.c.o.provides.build
.PHONY : src/serial0/CMakeFiles/serial0.dir/serial0.c.o.provides

src/serial0/CMakeFiles/serial0.dir/serial0.c.o.provides.build: src/serial0/CMakeFiles/serial0.dir/serial0.c.o

# Object files for target serial0
serial0_OBJECTS = \
"CMakeFiles/serial0.dir/serial0.c.o"

# External object files for target serial0
serial0_EXTERNAL_OBJECTS =

src/serial0/libserial0.a: src/serial0/CMakeFiles/serial0.dir/serial0.c.o
src/serial0/libserial0.a: src/serial0/CMakeFiles/serial0.dir/build.make
src/serial0/libserial0.a: src/serial0/CMakeFiles/serial0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libserial0.a"
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 && $(CMAKE_COMMAND) -P CMakeFiles/serial0.dir/cmake_clean_target.cmake
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/serial0/CMakeFiles/serial0.dir/build: src/serial0/libserial0.a
.PHONY : src/serial0/CMakeFiles/serial0.dir/build

src/serial0/CMakeFiles/serial0.dir/requires: src/serial0/CMakeFiles/serial0.dir/serial0.c.o.requires
.PHONY : src/serial0/CMakeFiles/serial0.dir/requires

src/serial0/CMakeFiles/serial0.dir/clean:
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 && $(CMAKE_COMMAND) -P CMakeFiles/serial0.dir/cmake_clean.cmake
.PHONY : src/serial0/CMakeFiles/serial0.dir/clean

src/serial0/CMakeFiles/serial0.dir/depend:
	cd /home/erwin/Documents/PRE/PES9EETAAS/theMain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erwin/Documents/PRE/PES9EETAAS/theMain /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 /home/erwin/Documents/PRE/PES9EETAAS/theMain /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0 /home/erwin/Documents/PRE/PES9EETAAS/theMain/src/serial0/CMakeFiles/serial0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/serial0/CMakeFiles/serial0.dir/depend

