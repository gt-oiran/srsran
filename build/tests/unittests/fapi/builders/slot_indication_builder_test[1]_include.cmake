if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/builders/slot_indication_builder_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/builders/slot_indication_builder_test[1]_tests.cmake")
else()
  add_test(slot_indication_builder_test_NOT_BUILT slot_indication_builder_test_NOT_BUILT)
endif()
