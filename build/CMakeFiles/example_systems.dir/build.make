# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/default/Projects/OECS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/default/Projects/OECS/build

# Include any dependencies generated for this target.
include CMakeFiles/example_systems.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/example_systems.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/example_systems.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example_systems.dir/flags.make

CMakeFiles/example_systems.dir/codegen:
.PHONY : CMakeFiles/example_systems.dir/codegen

CMakeFiles/example_systems.dir/examples/systems.c.o: CMakeFiles/example_systems.dir/flags.make
CMakeFiles/example_systems.dir/examples/systems.c.o: /home/default/Projects/OECS/examples/systems.c
CMakeFiles/example_systems.dir/examples/systems.c.o: CMakeFiles/example_systems.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/default/Projects/OECS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/example_systems.dir/examples/systems.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/example_systems.dir/examples/systems.c.o -MF CMakeFiles/example_systems.dir/examples/systems.c.o.d -o CMakeFiles/example_systems.dir/examples/systems.c.o -c /home/default/Projects/OECS/examples/systems.c

CMakeFiles/example_systems.dir/examples/systems.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/example_systems.dir/examples/systems.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/default/Projects/OECS/examples/systems.c > CMakeFiles/example_systems.dir/examples/systems.c.i

CMakeFiles/example_systems.dir/examples/systems.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/example_systems.dir/examples/systems.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/default/Projects/OECS/examples/systems.c -o CMakeFiles/example_systems.dir/examples/systems.c.s

# Object files for target example_systems
example_systems_OBJECTS = \
"CMakeFiles/example_systems.dir/examples/systems.c.o"

# External object files for target example_systems
example_systems_EXTERNAL_OBJECTS =

example_systems: CMakeFiles/example_systems.dir/examples/systems.c.o
example_systems: CMakeFiles/example_systems.dir/build.make
example_systems: CMakeFiles/example_systems.dir/compiler_depend.ts
example_systems: libOECS.so
example_systems: CMakeFiles/example_systems.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/default/Projects/OECS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable example_systems"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_systems.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example_systems.dir/build: example_systems
.PHONY : CMakeFiles/example_systems.dir/build

CMakeFiles/example_systems.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example_systems.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example_systems.dir/clean

CMakeFiles/example_systems.dir/depend:
	cd /home/default/Projects/OECS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/default/Projects/OECS /home/default/Projects/OECS /home/default/Projects/OECS/build /home/default/Projects/OECS/build /home/default/Projects/OECS/build/CMakeFiles/example_systems.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/example_systems.dir/depend

