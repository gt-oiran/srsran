if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/validators/rx_data_indication_validator_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/validators/rx_data_indication_validator_test[1]_tests.cmake")
else()
  add_test(rx_data_indication_validator_test_NOT_BUILT rx_data_indication_validator_test_NOT_BUILT)
endif()
