# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga

# Include any dependencies generated for this target.
include src/dessinterminal/CMakeFiles/dessinterminal.dir/depend.make

# Include the progress variables for this target.
include src/dessinterminal/CMakeFiles/dessinterminal.dir/progress.make

# Include the compile flags for this target's objects.
include src/dessinterminal/CMakeFiles/dessinterminal.dir/flags.make

src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o: src/dessinterminal/CMakeFiles/dessinterminal.dir/flags.make
src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o: src/dessinterminal/drawterminal.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o"
	cd /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/dessinterminal.dir/drawterminal.c.o   -c /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal/drawterminal.c

src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dessinterminal.dir/drawterminal.c.i"
	cd /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal/drawterminal.c > CMakeFiles/dessinterminal.dir/drawterminal.c.i

src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dessinterminal.dir/drawterminal.c.s"
	cd /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal/drawterminal.c -o CMakeFiles/dessinterminal.dir/drawterminal.c.s

src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.requires:
.PHONY : src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.requires

src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.provides: src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.requires
	$(MAKE) -f src/dessinterminal/CMakeFiles/dessinterminal.dir/build.make src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.provides.build
.PHONY : src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.provides

src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.provides.build: src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o

# Object files for target dessinterminal
dessinterminal_OBJECTS = \
"CMakeFiles/dessinterminal.dir/drawterminal.c.o"

# External object files for target dessinterminal
dessinterminal_EXTERNAL_OBJECTS =

src/dessinterminal/libdessinterminal.so: src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o
src/dessinterminal/libdessinterminal.so: src/dessinterminal/CMakeFiles/dessinterminal.dir/build.make
src/dessinterminal/libdessinterminal.so: src/dessinterminal/CMakeFiles/dessinterminal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libdessinterminal.so"
	cd /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dessinterminal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/dessinterminal/CMakeFiles/dessinterminal.dir/build: src/dessinterminal/libdessinterminal.so
.PHONY : src/dessinterminal/CMakeFiles/dessinterminal.dir/build

src/dessinterminal/CMakeFiles/dessinterminal.dir/requires: src/dessinterminal/CMakeFiles/dessinterminal.dir/drawterminal.c.o.requires
.PHONY : src/dessinterminal/CMakeFiles/dessinterminal.dir/requires

src/dessinterminal/CMakeFiles/dessinterminal.dir/clean:
	cd /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal && $(CMAKE_COMMAND) -P CMakeFiles/dessinterminal.dir/cmake_clean.cmake
.PHONY : src/dessinterminal/CMakeFiles/dessinterminal.dir/clean

src/dessinterminal/CMakeFiles/dessinterminal.dir/depend:
	cd /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal /home/erwin/Documents/S9/PRE/PES9EETAAS/dummyFpga/src/dessinterminal/CMakeFiles/dessinterminal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/dessinterminal/CMakeFiles/dessinterminal.dir/depend

