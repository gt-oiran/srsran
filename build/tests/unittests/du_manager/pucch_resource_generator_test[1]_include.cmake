if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/du_manager/pucch_resource_generator_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/du_manager/pucch_resource_generator_test[1]_tests.cmake")
else()
  add_test(pucch_resource_generator_test_NOT_BUILT pucch_resource_generator_test_NOT_BUILT)
endif()
