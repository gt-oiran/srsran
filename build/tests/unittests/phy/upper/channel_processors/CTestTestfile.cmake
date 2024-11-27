# CMake generated Testfile for 
# Source directory: /home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors
# Build directory: /home/bezerra/Workspace/srsran/build/tests/unittests/phy/upper/channel_processors
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pdcch_processor_unittest "pdcch_processor_unittest")
set_tests_properties(pdcch_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;32;add_test;/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pucch_processor_format1_unittest "pucch_processor_format1_unittest")
set_tests_properties(pucch_processor_format1_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;41;add_test;/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pucch_processor_validators_test "pucch_processor_validators_test")
set_tests_properties(pucch_processor_validators_test PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;55;add_test;/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(ssb_processor_unittest "ssb_processor_unittest")
set_tests_properties(ssb_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;59;add_test;/home/bezerra/Workspace/srsran/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
subdirs("pdsch")
subdirs("pusch")
subdirs("uci")
set_directory_properties(PROPERTIES LABELS "phy")
