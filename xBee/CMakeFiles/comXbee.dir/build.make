# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee

# Include any dependencies generated for this target.
include CMakeFiles/comXbee.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/comXbee.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/comXbee.dir/flags.make

CMakeFiles/comXbee.dir/src/checksum.c.o: CMakeFiles/comXbee.dir/flags.make
CMakeFiles/comXbee.dir/src/checksum.c.o: src/checksum.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/comXbee.dir/src/checksum.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/comXbee.dir/src/checksum.c.o   -c /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/checksum.c

CMakeFiles/comXbee.dir/src/checksum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/comXbee.dir/src/checksum.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/checksum.c > CMakeFiles/comXbee.dir/src/checksum.c.i

CMakeFiles/comXbee.dir/src/checksum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/comXbee.dir/src/checksum.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/checksum.c -o CMakeFiles/comXbee.dir/src/checksum.c.s

CMakeFiles/comXbee.dir/src/checksum.c.o.requires:

.PHONY : CMakeFiles/comXbee.dir/src/checksum.c.o.requires

CMakeFiles/comXbee.dir/src/checksum.c.o.provides: CMakeFiles/comXbee.dir/src/checksum.c.o.requires
	$(MAKE) -f CMakeFiles/comXbee.dir/build.make CMakeFiles/comXbee.dir/src/checksum.c.o.provides.build
.PHONY : CMakeFiles/comXbee.dir/src/checksum.c.o.provides

CMakeFiles/comXbee.dir/src/checksum.c.o.provides.build: CMakeFiles/comXbee.dir/src/checksum.c.o


CMakeFiles/comXbee.dir/src/comXbee.c.o: CMakeFiles/comXbee.dir/flags.make
CMakeFiles/comXbee.dir/src/comXbee.c.o: src/comXbee.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/comXbee.dir/src/comXbee.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/comXbee.dir/src/comXbee.c.o   -c /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/comXbee.c

CMakeFiles/comXbee.dir/src/comXbee.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/comXbee.dir/src/comXbee.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/comXbee.c > CMakeFiles/comXbee.dir/src/comXbee.c.i

CMakeFiles/comXbee.dir/src/comXbee.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/comXbee.dir/src/comXbee.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/comXbee.c -o CMakeFiles/comXbee.dir/src/comXbee.c.s

CMakeFiles/comXbee.dir/src/comXbee.c.o.requires:

.PHONY : CMakeFiles/comXbee.dir/src/comXbee.c.o.requires

CMakeFiles/comXbee.dir/src/comXbee.c.o.provides: CMakeFiles/comXbee.dir/src/comXbee.c.o.requires
	$(MAKE) -f CMakeFiles/comXbee.dir/build.make CMakeFiles/comXbee.dir/src/comXbee.c.o.provides.build
.PHONY : CMakeFiles/comXbee.dir/src/comXbee.c.o.provides

CMakeFiles/comXbee.dir/src/comXbee.c.o.provides.build: CMakeFiles/comXbee.dir/src/comXbee.c.o


CMakeFiles/comXbee.dir/src/serial0.c.o: CMakeFiles/comXbee.dir/flags.make
CMakeFiles/comXbee.dir/src/serial0.c.o: src/serial0.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/comXbee.dir/src/serial0.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/comXbee.dir/src/serial0.c.o   -c /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/serial0.c

CMakeFiles/comXbee.dir/src/serial0.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/comXbee.dir/src/serial0.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/serial0.c > CMakeFiles/comXbee.dir/src/serial0.c.i

CMakeFiles/comXbee.dir/src/serial0.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/comXbee.dir/src/serial0.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/src/serial0.c -o CMakeFiles/comXbee.dir/src/serial0.c.s

CMakeFiles/comXbee.dir/src/serial0.c.o.requires:

.PHONY : CMakeFiles/comXbee.dir/src/serial0.c.o.requires

CMakeFiles/comXbee.dir/src/serial0.c.o.provides: CMakeFiles/comXbee.dir/src/serial0.c.o.requires
	$(MAKE) -f CMakeFiles/comXbee.dir/build.make CMakeFiles/comXbee.dir/src/serial0.c.o.provides.build
.PHONY : CMakeFiles/comXbee.dir/src/serial0.c.o.provides

CMakeFiles/comXbee.dir/src/serial0.c.o.provides.build: CMakeFiles/comXbee.dir/src/serial0.c.o


# Object files for target comXbee
comXbee_OBJECTS = \
"CMakeFiles/comXbee.dir/src/checksum.c.o" \
"CMakeFiles/comXbee.dir/src/comXbee.c.o" \
"CMakeFiles/comXbee.dir/src/serial0.c.o"

# External object files for target comXbee
comXbee_EXTERNAL_OBJECTS =

comXbee: CMakeFiles/comXbee.dir/src/checksum.c.o
comXbee: CMakeFiles/comXbee.dir/src/comXbee.c.o
comXbee: CMakeFiles/comXbee.dir/src/serial0.c.o
comXbee: CMakeFiles/comXbee.dir/build.make
comXbee: CMakeFiles/comXbee.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable comXbee"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comXbee.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/comXbee.dir/build: comXbee

.PHONY : CMakeFiles/comXbee.dir/build

CMakeFiles/comXbee.dir/requires: CMakeFiles/comXbee.dir/src/checksum.c.o.requires
CMakeFiles/comXbee.dir/requires: CMakeFiles/comXbee.dir/src/comXbee.c.o.requires
CMakeFiles/comXbee.dir/requires: CMakeFiles/comXbee.dir/src/serial0.c.o.requires

.PHONY : CMakeFiles/comXbee.dir/requires

CMakeFiles/comXbee.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/comXbee.dir/cmake_clean.cmake
.PHONY : CMakeFiles/comXbee.dir/clean

CMakeFiles/comXbee.dir/depend:
	cd /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee /Users/erwinandre/Documents/ENIB/PRE/PES9EETAAS/xBee/CMakeFiles/comXbee.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/comXbee.dir/depend

