# CMake generated Testfile for 
# Source directory: /home/bezerra/Workspace/srsran/tests/unittests/phy/generic_functions
# Build directory: /home/bezerra/Workspace/srsran/build/tests/unittests/phy/generic_functions
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(dft_processor_generic_test "dft_processor_test" "-F" "generic" "-R" "10")
set_tests_properties(dft_processor_generic_test PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/unittests/phy/generic_functions/CMakeLists.txt;32;add_test;/home/bezerra/Workspace/srsran/tests/unittests/phy/generic_functions/CMakeLists.txt;0;")
add_test(dft_processor_fftw_test "dft_processor_test" "-F" "fftw" "-R" "10")
set_tests_properties(dft_processor_fftw_test PROPERTIES  _BACKTRACE_TRIPLES "/home/bezerra/Workspace/srsran/tests/unittests/phy/generic_functions/CMakeLists.txt;34;add_test;/home/bezerra/Workspace/srsran/tests/unittests/phy/generic_functions/CMakeLists.txt;0;")
subdirs("precoding")
subdirs("transform_precoding")
set_directory_properties(PROPERTIES LABELS "phy")
