if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/nru/nru_packing_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/nru/nru_packing_test[1]_tests.cmake")
else()
  add_test(nru_packing_test_NOT_BUILT nru_packing_test_NOT_BUILT)
endif()
