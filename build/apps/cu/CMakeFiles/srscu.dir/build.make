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
include apps/cu/CMakeFiles/srscu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include apps/cu/CMakeFiles/srscu.dir/compiler_depend.make

# Include the progress variables for this target.
include apps/cu/CMakeFiles/srscu.dir/progress.make

# Include the compile flags for this target's objects.
include apps/cu/CMakeFiles/srscu.dir/flags.make

apps/cu/CMakeFiles/srscu.dir/cu.cpp.o: apps/cu/CMakeFiles/srscu.dir/flags.make
apps/cu/CMakeFiles/srscu.dir/cu.cpp.o: ../apps/cu/cu.cpp
apps/cu/CMakeFiles/srscu.dir/cu.cpp.o: apps/cu/CMakeFiles/srscu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/cu/CMakeFiles/srscu.dir/cu.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/cu/CMakeFiles/srscu.dir/cu.cpp.o -MF CMakeFiles/srscu.dir/cu.cpp.o.d -o CMakeFiles/srscu.dir/cu.cpp.o -c /home/bezerra/Workspace/srsran/apps/cu/cu.cpp

apps/cu/CMakeFiles/srscu.dir/cu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srscu.dir/cu.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/apps/cu/cu.cpp > CMakeFiles/srscu.dir/cu.cpp.i

apps/cu/CMakeFiles/srscu.dir/cu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srscu.dir/cu.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/apps/cu/cu.cpp -o CMakeFiles/srscu.dir/cu.cpp.s

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o: apps/cu/CMakeFiles/srscu.dir/flags.make
apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o: ../apps/cu/cu_appconfig_cli11_schema.cpp
apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o: apps/cu/CMakeFiles/srscu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o -MF CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o.d -o CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o -c /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_cli11_schema.cpp

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_cli11_schema.cpp > CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.i

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_cli11_schema.cpp -o CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.s

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o: apps/cu/CMakeFiles/srscu.dir/flags.make
apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o: ../apps/cu/cu_appconfig_validator.cpp
apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o: apps/cu/CMakeFiles/srscu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o -MF CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o.d -o CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o -c /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_validator.cpp

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_validator.cpp > CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.i

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_validator.cpp -o CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.s

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o: apps/cu/CMakeFiles/srscu.dir/flags.make
apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o: ../apps/cu/cu_appconfig_yaml_writer.cpp
apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o: apps/cu/CMakeFiles/srscu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o -MF CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o.d -o CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o -c /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_yaml_writer.cpp

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_yaml_writer.cpp > CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.i

apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/apps/cu/cu_appconfig_yaml_writer.cpp -o CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.s

apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o: apps/cu/CMakeFiles/srscu.dir/flags.make
apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o: ../apps/gnb/gnb_appconfig_translators.cpp
apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o: apps/cu/CMakeFiles/srscu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/bin/ccache /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o -MF CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o.d -o CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o -c /home/bezerra/Workspace/srsran/apps/gnb/gnb_appconfig_translators.cpp

apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.i"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bezerra/Workspace/srsran/apps/gnb/gnb_appconfig_translators.cpp > CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.i

apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.s"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bezerra/Workspace/srsran/apps/gnb/gnb_appconfig_translators.cpp -o CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.s

# Object files for target srscu
srscu_OBJECTS = \
"CMakeFiles/srscu.dir/cu.cpp.o" \
"CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o" \
"CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o" \
"CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o" \
"CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o"

# External object files for target srscu
srscu_EXTERNAL_OBJECTS =

apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/cu.cpp.o
apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/cu_appconfig_cli11_schema.cpp.o
apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/cu_appconfig_validator.cpp.o
apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/cu_appconfig_yaml_writer.cpp.o
apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/__/gnb/gnb_appconfig_translators.cpp.o
apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/build.make
apps/cu/srscu: apps/services/libsrsran_app_services.a
apps/cu/srscu: lib/support/libsrsran_support.a
apps/cu/srscu: lib/support/versioning/libsrsran_versioning.a
apps/cu/srscu: apps/units/cu_cp/libsrsran_cu_cp_app_unit.a
apps/cu/srscu: apps/units/cu_up/libsrsran_cu_up_app_unit.a
apps/cu/srscu: lib/ngap/libsrsran_ngap.a
apps/cu/srscu: lib/f1ap/gateways/libsrsran_f1c_gateway.a
apps/cu/srscu: lib/e1ap/gateways/libsrsran_e1_gateway.a
apps/cu/srscu: lib/e2/libsrsran_e2.a
apps/cu/srscu: lib/f1u/libsrsgnb_app_f1u_cu_up_split_connector.a
apps/cu/srscu: lib/pcap/libsrsran_pcap.a
apps/cu/srscu: lib/asn1/libngap_asn1.a
apps/cu/srscu: apps/services/logger/libsrsran_logger_app_service.a
apps/cu/srscu: apps/services/buffer_pool/libsrsran_buffer_pool_app_service.a
apps/cu/srscu: lib/cu_up/libsrsran_cu_up.a
apps/cu/srscu: lib/e1ap/cu_up/libsrsran_e1ap_cu_up.a
apps/cu/srscu: lib/gtpu/libsrsran_gtpu.a
apps/cu/srscu: lib/nru/libsrsran_nru.a
apps/cu/srscu: lib/psup/libsrsran_psup.a
apps/cu/srscu: lib/gateways/libsrsran_gateway.a
apps/cu/srscu: /usr/lib/x86_64-linux-gnu/libsctp.so
apps/cu/srscu: lib/sdap/libsrsran_sdap.a
apps/cu/srscu: lib/cu_cp/libsrsran_cu_cp.a
apps/cu/srscu: lib/e1ap/cu_cp/libsrsran_e1ap_cu_cp.a
apps/cu/srscu: lib/ngap/libsrsran_ngap.a
apps/cu/srscu: lib/cu_cp/libsrsran_cu_cp.a
apps/cu/srscu: lib/e1ap/cu_cp/libsrsran_e1ap_cu_cp.a
apps/cu/srscu: lib/asn1/libngap_asn1.a
apps/cu/srscu: lib/e2/libsrsran_e2.a
apps/cu/srscu: lib/asn1/libe2ap_asn1.a
apps/cu/srscu: lib/cu_cp/cell_meas_manager/libsrsran_cu_cp_cell_meas_manager.a
apps/cu/srscu: lib/cu_cp/mobility_manager/libsrsran_cu_cp_mobility_manager.a
apps/cu/srscu: lib/f1ap/cu_cp/libsrsran_f1ap_cu.a
apps/cu/srscu: lib/f1ap/libsrsran_f1ap_common.a
apps/cu/srscu: lib/rrc/libsrsran_rrc.a
apps/cu/srscu: lib/pdcp/libsrsran_pdcp.a
apps/cu/srscu: lib/instrumentation/libsrsran_instrumentation.a
apps/cu/srscu: lib/security/libsrsran_security.a
apps/cu/srscu: /usr/lib/x86_64-linux-gnu/libmbedcrypto.so
apps/cu/srscu: lib/cu_cp/ue_security_manager/libsrsran_ue_security_manager.a
apps/cu/srscu: lib/cu_cp/up_resource_manager/libsrsran_up_resource_manager.a
apps/cu/srscu: lib/asn1/rrc_nr/librrc_nr_asn1.a
apps/cu/srscu: lib/ran/libsrsran_ran.a
apps/cu/srscu: lib/asn1/libf1ap_asn1.a
apps/cu/srscu: lib/e1ap/common/libsrsran_e1ap_common.a
apps/cu/srscu: lib/asn1/libe1ap_asn1.a
apps/cu/srscu: lib/asn1/libasn1_utils.a
apps/cu/srscu: lib/support/libsrsran_support.a
apps/cu/srscu: lib/support/network/libsrsran_network.a
apps/cu/srscu: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
apps/cu/srscu: lib/srslog/libsrslog.a
apps/cu/srscu: external/fmt/libfmt.a
apps/cu/srscu: lib/f1u/libsrsran_f1u_cu_up.a
apps/cu/srscu: apps/cu/CMakeFiles/srscu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bezerra/Workspace/srsran/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable srscu"
	cd /home/bezerra/Workspace/srsran/build/apps/cu && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/srscu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/cu/CMakeFiles/srscu.dir/build: apps/cu/srscu
.PHONY : apps/cu/CMakeFiles/srscu.dir/build

apps/cu/CMakeFiles/srscu.dir/clean:
	cd /home/bezerra/Workspace/srsran/build/apps/cu && $(CMAKE_COMMAND) -P CMakeFiles/srscu.dir/cmake_clean.cmake
.PHONY : apps/cu/CMakeFiles/srscu.dir/clean

apps/cu/CMakeFiles/srscu.dir/depend:
	cd /home/bezerra/Workspace/srsran/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bezerra/Workspace/srsran /home/bezerra/Workspace/srsran/apps/cu /home/bezerra/Workspace/srsran/build /home/bezerra/Workspace/srsran/build/apps/cu /home/bezerra/Workspace/srsran/build/apps/cu/CMakeFiles/srscu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/cu/CMakeFiles/srscu.dir/depend

