if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/validators/crc_indication_validator_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/validators/crc_indication_validator_test[1]_tests.cmake")
else()
  add_test(crc_indication_validator_test_NOT_BUILT crc_indication_validator_test_NOT_BUILT)
endif()
