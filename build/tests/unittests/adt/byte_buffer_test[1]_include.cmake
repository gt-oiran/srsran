if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/adt/byte_buffer_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/adt/byte_buffer_test[1]_tests.cmake")
else()
  add_test(byte_buffer_test_NOT_BUILT byte_buffer_test_NOT_BUILT)
endif()
