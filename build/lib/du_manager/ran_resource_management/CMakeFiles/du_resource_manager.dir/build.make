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
include lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/progress.make

# Include the compile flags for this target's objects.
include lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/flags.make

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/flags.make
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o: ../lib/du_manager/ran_resource_management/du_ran_resource_manager_impl.cpp
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o -MF CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o.d -o CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o -c /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/du_ran_resource_manager_impl.cpp

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/du_ran_resource_manager_impl.cpp > CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.i

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/du_ran_resource_manager_impl.cpp -o CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.s

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/flags.make
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o: ../lib/du_manager/ran_resource_management/du_pucch_resource_manager.cpp
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o -MF CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o.d -o CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o -c /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/du_pucch_resource_manager.cpp

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/du_pucch_resource_manager.cpp > CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.i

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/du_pucch_resource_manager.cpp -o CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.s

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/flags.make
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o: ../lib/du_manager/ran_resource_management/pucch_resource_generator.cpp
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o -MF CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o.d -o CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o -c /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/pucch_resource_generator.cpp

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/pucch_resource_generator.cpp > CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.i

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management/pucch_resource_generator.cpp -o CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.s

# Object files for target du_resource_manager
du_resource_manager_OBJECTS = \
"CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o" \
"CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o" \
"CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o"

# External object files for target du_resource_manager
du_resource_manager_EXTERNAL_OBJECTS =

lib/du_manager/ran_resource_management/libdu_resource_manager.a: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_ran_resource_manager_impl.cpp.o
lib/du_manager/ran_resource_management/libdu_resource_manager.a: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/du_pucch_resource_manager.cpp.o
lib/du_manager/ran_resource_management/libdu_resource_manager.a: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/pucch_resource_generator.cpp.o
lib/du_manager/ran_resource_management/libdu_resource_manager.a: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/build.make
lib/du_manager/ran_resource_management/libdu_resource_manager.a: lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libdu_resource_manager.a"
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && $(CMAKE_COMMAND) -P CMakeFiles/du_resource_manager.dir/cmake_clean_target.cmake
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/du_resource_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/build: lib/du_manager/ran_resource_management/libdu_resource_manager.a
.PHONY : lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/build

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/clean:
	cd /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management && $(CMAKE_COMMAND) -P CMakeFiles/du_resource_manager.dir/cmake_clean.cmake
.PHONY : lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/clean

lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/depend:
	cd /home/bezerra/Workspace/srsran/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bezerra/Workspace/srsran /home/bezerra/Workspace/srsran/lib/du_manager/ran_resource_management /home/bezerra/Workspace/srsran/build /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management /home/bezerra/Workspace/srsran/build/lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/du_manager/ran_resource_management/CMakeFiles/du_resource_manager.dir/depend

