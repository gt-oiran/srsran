if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/scheduler/cell/scheduler_cell_resource_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/scheduler/cell/scheduler_cell_resource_test[1]_tests.cmake")
else()
  add_test(scheduler_cell_resource_test_NOT_BUILT scheduler_cell_resource_test_NOT_BUILT)
endif()
