if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/gtpu/gtpu_tunnel_ngu_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/gtpu/gtpu_tunnel_ngu_test[1]_tests.cmake")
else()
  add_test(gtpu_tunnel_ngu_test_NOT_BUILT gtpu_tunnel_ngu_test_NOT_BUILT)
endif()
