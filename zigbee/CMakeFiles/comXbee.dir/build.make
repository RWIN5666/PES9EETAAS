# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/erwin/Documents/PROJETELEC/Tests/cMake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erwin/Documents/PROJETELEC/Tests/cMake

# Include any dependencies generated for this target.
include CMakeFiles/comXbee.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/comXbee.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/comXbee.dir/flags.make

CMakeFiles/comXbee.dir/main/comXbee.c.o: CMakeFiles/comXbee.dir/flags.make
CMakeFiles/comXbee.dir/main/comXbee.c.o: main/comXbee.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PROJETELEC/Tests/cMake/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/comXbee.dir/main/comXbee.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/comXbee.dir/main/comXbee.c.o   -c /home/erwin/Documents/PROJETELEC/Tests/cMake/main/comXbee.c

CMakeFiles/comXbee.dir/main/comXbee.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/comXbee.dir/main/comXbee.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PROJETELEC/Tests/cMake/main/comXbee.c > CMakeFiles/comXbee.dir/main/comXbee.c.i

CMakeFiles/comXbee.dir/main/comXbee.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/comXbee.dir/main/comXbee.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PROJETELEC/Tests/cMake/main/comXbee.c -o CMakeFiles/comXbee.dir/main/comXbee.c.s

CMakeFiles/comXbee.dir/main/comXbee.c.o.requires:
.PHONY : CMakeFiles/comXbee.dir/main/comXbee.c.o.requires

CMakeFiles/comXbee.dir/main/comXbee.c.o.provides: CMakeFiles/comXbee.dir/main/comXbee.c.o.requires
	$(MAKE) -f CMakeFiles/comXbee.dir/build.make CMakeFiles/comXbee.dir/main/comXbee.c.o.provides.build
.PHONY : CMakeFiles/comXbee.dir/main/comXbee.c.o.provides

CMakeFiles/comXbee.dir/main/comXbee.c.o.provides.build: CMakeFiles/comXbee.dir/main/comXbee.c.o
.PHONY : CMakeFiles/comXbee.dir/main/comXbee.c.o.provides.build

# Object files for target comXbee
comXbee_OBJECTS = \
"CMakeFiles/comXbee.dir/main/comXbee.c.o"

# External object files for target comXbee
comXbee_EXTERNAL_OBJECTS =

comXbee: CMakeFiles/comXbee.dir/main/comXbee.c.o
comXbee: src/serial/libserial.so
comXbee: src/zigbee/libzigbee.so
comXbee: CMakeFiles/comXbee.dir/build.make
comXbee: CMakeFiles/comXbee.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable comXbee"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comXbee.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/comXbee.dir/build: comXbee
.PHONY : CMakeFiles/comXbee.dir/build

CMakeFiles/comXbee.dir/requires: CMakeFiles/comXbee.dir/main/comXbee.c.o.requires
.PHONY : CMakeFiles/comXbee.dir/requires

CMakeFiles/comXbee.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/comXbee.dir/cmake_clean.cmake
.PHONY : CMakeFiles/comXbee.dir/clean

CMakeFiles/comXbee.dir/depend:
	cd /home/erwin/Documents/PROJETELEC/Tests/cMake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erwin/Documents/PROJETELEC/Tests/cMake /home/erwin/Documents/PROJETELEC/Tests/cMake /home/erwin/Documents/PROJETELEC/Tests/cMake /home/erwin/Documents/PROJETELEC/Tests/cMake /home/erwin/Documents/PROJETELEC/Tests/cMake/CMakeFiles/comXbee.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/comXbee.dir/depend
