# CMake generated Testfile for 
# Source directory: /home/bezerra/Workspace/srsran/tests/integrationtests/phy/upper/channel_processors
# Build directory: /home/bezerra/Workspace/srsran/build/tests/integrationtests/phy/upper/channel_processors
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/bezerra/Workspace/srsran/build/tests/integrationtests/phy/upper/channel_processors/pxsch_chain_test[1]_include.cmake")
add_test(pxsch_bler_test "pxsch_bler_test" "-R" "10")
set_tests_properties(pxsch_bler_test PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/integrationtests/phy/upper/channel_processors/CMakeLists.txt;42;add_test;/home/bezerra/Workspace/srsran/tests/integrationtests/phy/upper/channel_processors/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "phy;tsan;NO_MEMCHECK")
