if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi_adaptor/mac/mac_to_fapi_translator_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi_adaptor/mac/mac_to_fapi_translator_test[1]_tests.cmake")
else()
  add_test(mac_to_fapi_translator_test_NOT_BUILT mac_to_fapi_translator_test_NOT_BUILT)
endif()
