if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/security/security_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/security/security_test[1]_tests.cmake")
else()
  add_test(security_test_NOT_BUILT security_test_NOT_BUILT)
endif()
