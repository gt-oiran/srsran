if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/builders/rach_indication_builder_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/builders/rach_indication_builder_test[1]_tests.cmake")
else()
  add_test(rach_indication_builder_test_NOT_BUILT rach_indication_builder_test_NOT_BUILT)
endif()
