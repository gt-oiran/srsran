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
include tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/progress.make

# Include the compile flags for this target's objects.
include tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/flags.make

tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o: tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/flags.make
tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o: ../tests/unittests/f1ap/cu_cp/f1ap_cu_test_helpers.cpp
tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o: tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o -MF CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o.d -o CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o -c /home/bezerra/Workspace/srsran/tests/unittests/f1ap/cu_cp/f1ap_cu_test_helpers.cpp

tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/tests/unittests/f1ap/cu_cp/f1ap_cu_test_helpers.cpp > CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.i

tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/tests/unittests/f1ap/cu_cp/f1ap_cu_test_helpers.cpp -o CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.s

# Object files for target f1ap_cu_test_helpers
f1ap_cu_test_helpers_OBJECTS = \
"CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o"

# External object files for target f1ap_cu_test_helpers
f1ap_cu_test_helpers_EXTERNAL_OBJECTS =

tests/unittests/f1ap/cu_cp/libf1ap_cu_test_helpers.a: tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/f1ap_cu_test_helpers.cpp.o
tests/unittests/f1ap/cu_cp/libf1ap_cu_test_helpers.a: tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/build.make
tests/unittests/f1ap/cu_cp/libf1ap_cu_test_helpers.a: tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libf1ap_cu_test_helpers.a"
	cd /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp && $(CMAKE_COMMAND) -P CMakeFiles/f1ap_cu_test_helpers.dir/cmake_clean_target.cmake
	cd /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/f1ap_cu_test_helpers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/build: tests/unittests/f1ap/cu_cp/libf1ap_cu_test_helpers.a
.PHONY : tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/build

tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/clean:
	cd /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp && $(CMAKE_COMMAND) -P CMakeFiles/f1ap_cu_test_helpers.dir/cmake_clean.cmake
.PHONY : tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/clean

tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/depend:
	cd /home/bezerra/Workspace/srsran/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bezerra/Workspace/srsran /home/bezerra/Workspace/srsran/tests/unittests/f1ap/cu_cp /home/bezerra/Workspace/srsran/build /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp /home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/unittests/f1ap/cu_cp/CMakeFiles/f1ap_cu_test_helpers.dir/depend

