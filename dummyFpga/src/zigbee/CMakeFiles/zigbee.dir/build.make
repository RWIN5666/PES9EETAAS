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
CMAKE_SOURCE_DIR = /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga

# Include any dependencies generated for this target.
include src/zigbee/CMakeFiles/zigbee.dir/depend.make

# Include the progress variables for this target.
include src/zigbee/CMakeFiles/zigbee.dir/progress.make

# Include the compile flags for this target's objects.
include src/zigbee/CMakeFiles/zigbee.dir/flags.make

src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o: src/zigbee/CMakeFiles/zigbee.dir/flags.make
src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o: src/zigbee/zigbeeLib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zigbee.dir/zigbeeLib.c.o   -c /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/zigbeeLib.c

src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zigbee.dir/zigbeeLib.c.i"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/zigbeeLib.c > CMakeFiles/zigbee.dir/zigbeeLib.c.i

src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zigbee.dir/zigbeeLib.c.s"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/zigbeeLib.c -o CMakeFiles/zigbee.dir/zigbeeLib.c.s

src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.requires:
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.requires

src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.provides: src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.requires
	$(MAKE) -f src/zigbee/CMakeFiles/zigbee.dir/build.make src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.provides.build
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.provides

src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.provides.build: src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o

src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o: src/zigbee/CMakeFiles/zigbee.dir/flags.make
src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o: src/zigbee/checksum.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zigbee.dir/checksum.c.o   -c /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/checksum.c

src/zigbee/CMakeFiles/zigbee.dir/checksum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zigbee.dir/checksum.c.i"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/checksum.c > CMakeFiles/zigbee.dir/checksum.c.i

src/zigbee/CMakeFiles/zigbee.dir/checksum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zigbee.dir/checksum.c.s"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/checksum.c -o CMakeFiles/zigbee.dir/checksum.c.s

src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.requires:
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.requires

src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.provides: src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.requires
	$(MAKE) -f src/zigbee/CMakeFiles/zigbee.dir/build.make src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.provides.build
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.provides

src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.provides.build: src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o

src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o: src/zigbee/CMakeFiles/zigbee.dir/flags.make
src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o: src/zigbee/fpgalib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zigbee.dir/fpgalib.c.o   -c /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/fpgalib.c

src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zigbee.dir/fpgalib.c.i"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/fpgalib.c > CMakeFiles/zigbee.dir/fpgalib.c.i

src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zigbee.dir/fpgalib.c.s"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/fpgalib.c -o CMakeFiles/zigbee.dir/fpgalib.c.s

src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.requires:
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.requires

src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.provides: src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.requires
	$(MAKE) -f src/zigbee/CMakeFiles/zigbee.dir/build.make src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.provides.build
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.provides

src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.provides.build: src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o

# Object files for target zigbee
zigbee_OBJECTS = \
"CMakeFiles/zigbee.dir/zigbeeLib.c.o" \
"CMakeFiles/zigbee.dir/checksum.c.o" \
"CMakeFiles/zigbee.dir/fpgalib.c.o"

# External object files for target zigbee
zigbee_EXTERNAL_OBJECTS =

src/zigbee/libzigbee.so: src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o
src/zigbee/libzigbee.so: src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o
src/zigbee/libzigbee.so: src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o
src/zigbee/libzigbee.so: src/zigbee/CMakeFiles/zigbee.dir/build.make
src/zigbee/libzigbee.so: src/zigbee/CMakeFiles/zigbee.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libzigbee.so"
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zigbee.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/zigbee/CMakeFiles/zigbee.dir/build: src/zigbee/libzigbee.so
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/build

src/zigbee/CMakeFiles/zigbee.dir/requires: src/zigbee/CMakeFiles/zigbee.dir/zigbeeLib.c.o.requires
src/zigbee/CMakeFiles/zigbee.dir/requires: src/zigbee/CMakeFiles/zigbee.dir/checksum.c.o.requires
src/zigbee/CMakeFiles/zigbee.dir/requires: src/zigbee/CMakeFiles/zigbee.dir/fpgalib.c.o.requires
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/requires

src/zigbee/CMakeFiles/zigbee.dir/clean:
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee && $(CMAKE_COMMAND) -P CMakeFiles/zigbee.dir/cmake_clean.cmake
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/clean

src/zigbee/CMakeFiles/zigbee.dir/depend:
	cd /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee /home/erwin/Documents/PRE/PES9EETAAS/dummyFpga/src/zigbee/CMakeFiles/zigbee.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/zigbee/CMakeFiles/zigbee.dir/depend

