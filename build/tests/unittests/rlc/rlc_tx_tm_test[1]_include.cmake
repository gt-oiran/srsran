if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/rlc/rlc_tx_tm_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/rlc/rlc_tx_tm_test[1]_tests.cmake")
else()
  add_test(rlc_tx_tm_test_NOT_BUILT rlc_tx_tm_test_NOT_BUILT)
endif()
