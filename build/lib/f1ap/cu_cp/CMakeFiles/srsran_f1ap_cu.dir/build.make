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
include lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/progress.make

# Include the compile flags for this target's objects.
include lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o: ../lib/f1ap/cu_cp/f1ap_cu_impl.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/f1ap_cu_impl.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/f1ap_cu_impl.cpp > CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/f1ap_cu_impl.cpp -o CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o: ../lib/f1ap/cu_cp/f1ap_cu_factory.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/f1ap_cu_factory.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/f1ap_cu_factory.cpp > CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/f1ap_cu_factory.cpp -o CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o: ../lib/f1ap/cu_cp/procedures/f1_setup_procedure.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1_setup_procedure.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1_setup_procedure.cpp > CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1_setup_procedure.cpp -o CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o: ../lib/f1ap/cu_cp/procedures/f1_removal_procedure.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1_removal_procedure.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1_removal_procedure.cpp > CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1_removal_procedure.cpp -o CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o: ../lib/f1ap/cu_cp/procedures/f1ap_stop_procedure.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1ap_stop_procedure.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1ap_stop_procedure.cpp > CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/f1ap_stop_procedure.cpp -o CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o: ../lib/f1ap/cu_cp/procedures/ue_context_setup_procedure.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_setup_procedure.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_setup_procedure.cpp > CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_setup_procedure.cpp -o CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o: ../lib/f1ap/cu_cp/procedures/ue_context_modification_procedure.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_modification_procedure.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_modification_procedure.cpp > CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_modification_procedure.cpp -o CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.s

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/flags.make
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o: ../lib/f1ap/cu_cp/procedures/ue_context_release_procedure.cpp
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o -MF CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o.d -o CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o -c /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_release_procedure.cpp

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_release_procedure.cpp > CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.i

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp/procedures/ue_context_release_procedure.cpp -o CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.s

# Object files for target srsran_f1ap_cu
srsran_f1ap_cu_OBJECTS = \
"CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o" \
"CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o"

# External object files for target srsran_f1ap_cu
srsran_f1ap_cu_EXTERNAL_OBJECTS =

lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_impl.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/f1ap_cu_factory.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_setup_procedure.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1_removal_procedure.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/f1ap_stop_procedure.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_setup_procedure.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_modification_procedure.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/procedures/ue_context_release_procedure.cpp.o
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/build.make
lib/f1ap/cu_cp/libsrsran_f1ap_cu.a: lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libsrsran_f1ap_cu.a"
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && $(CMAKE_COMMAND) -P CMakeFiles/srsran_f1ap_cu.dir/cmake_clean_target.cmake
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/srsran_f1ap_cu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/build: lib/f1ap/cu_cp/libsrsran_f1ap_cu.a
.PHONY : lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/build

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/clean:
	cd /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp && $(CMAKE_COMMAND) -P CMakeFiles/srsran_f1ap_cu.dir/cmake_clean.cmake
.PHONY : lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/clean

lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/depend:
	cd /home/bezerra/Workspace/srsran/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bezerra/Workspace/srsran /home/bezerra/Workspace/srsran/lib/f1ap/cu_cp /home/bezerra/Workspace/srsran/build /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp /home/bezerra/Workspace/srsran/build/lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/f1ap/cu_cp/CMakeFiles/srsran_f1ap_cu.dir/depend

