if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/du_manager/du_ran_resource_manager_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/du_manager/du_ran_resource_manager_test[1]_tests.cmake")
else()
  add_test(du_ran_resource_manager_test_NOT_BUILT du_ran_resource_manager_test_NOT_BUILT)
endif()
