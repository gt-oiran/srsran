# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/bezerra/Workspace/srsran

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bezerra/Workspace/srsran/build

# Include any dependencies generated for this target.
include lib/support/versioning/CMakeFiles/srsran_versioning.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/support/versioning/CMakeFiles/srsran_versioning.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/support/versioning/CMakeFiles/srsran_versioning.dir/progress.make

# Include the compile flags for this target's objects.
include lib/support/versioning/CMakeFiles/srsran_versioning.dir/flags.make

lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.o: lib/support/versioning/CMakeFiles/srsran_versioning.dir/flags.make
lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.o: ../lib/support/versioning/build_info.cpp
lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.o: lib/support/versioning/CMakeFiles/srsran_versioning.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.o -MF CMakeFiles/srsran_versioning.dir/build_info.cpp.o.d -o CMakeFiles/srsran_versioning.dir/build_info.cpp.o -c /home/bezerra/Workspace/srsran/lib/support/versioning/build_info.cpp

lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_versioning.dir/build_info.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/support/versioning/build_info.cpp > CMakeFiles/srsran_versioning.dir/build_info.cpp.i

lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_versioning.dir/build_info.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/support/versioning/build_info.cpp -o CMakeFiles/srsran_versioning.dir/build_info.cpp.s

lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.o: lib/support/versioning/CMakeFiles/srsran_versioning.dir/flags.make
lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.o: ../lib/support/versioning/version.cpp
lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.o: lib/support/versioning/CMakeFiles/srsran_versioning.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.o -MF CMakeFiles/srsran_versioning.dir/version.cpp.o.d -o CMakeFiles/srsran_versioning.dir/version.cpp.o -c /home/bezerra/Workspace/srsran/lib/support/versioning/version.cpp

lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_versioning.dir/version.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/support/versioning/version.cpp > CMakeFiles/srsran_versioning.dir/version.cpp.i

lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_versioning.dir/version.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/support/versioning/version.cpp -o CMakeFiles/srsran_versioning.dir/version.cpp.s

# Object files for target srsran_versioning
srsran_versioning_OBJECTS = \
"CMakeFiles/srsran_versioning.dir/build_info.cpp.o" \
"CMakeFiles/srsran_versioning.dir/version.cpp.o"

# External object files for target srsran_versioning
srsran_versioning_EXTERNAL_OBJECTS =

lib/support/versioning/libsrsran_versioning.a: lib/support/versioning/CMakeFiles/srsran_versioning.dir/build_info.cpp.o
lib/support/versioning/libsrsran_versioning.a: lib/support/versioning/CMakeFiles/srsran_versioning.dir/version.cpp.o
lib/support/versioning/libsrsran_versioning.a: lib/support/versioning/CMakeFiles/srsran_versioning.dir/build.make
lib/support/versioning/libsrsran_versioning.a: lib/support/versioning/CMakeFiles/srsran_versioning.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libsrsran_versioning.a"
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && $(CMAKE_COMMAND) -P CMakeFiles/srsran_versioning.dir/cmake_clean_target.cmake
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/srsran_versioning.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/support/versioning/CMakeFiles/srsran_versioning.dir/build: lib/support/versioning/libsrsran_versioning.a
.PHONY : lib/support/versioning/CMakeFiles/srsran_versioning.dir/build

lib/support/versioning/CMakeFiles/srsran_versioning.dir/clean:
	cd /home/bezerra/Workspace/srsran/build/lib/support/versioning && $(CMAKE_COMMAND) -P CMakeFiles/srsran_versioning.dir/cmake_clean.cmake
.PHONY : lib/support/versioning/CMakeFiles/srsran_versioning.dir/clean

lib/support/versioning/CMakeFiles/srsran_versioning.dir/depend:
	cd /home/bezerra/Workspace/srsran/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bezerra/Workspace/srsran /home/bezerra/Workspace/srsran/lib/support/versioning /home/bezerra/Workspace/srsran/build /home/bezerra/Workspace/srsran/build/lib/support/versioning /home/bezerra/Workspace/srsran/build/lib/support/versioning/CMakeFiles/srsran_versioning.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/support/versioning/CMakeFiles/srsran_versioning.dir/depend

