if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/du/f1ap_du_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/f1ap/du/f1ap_du_test[1]_tests.cmake")
else()
  add_test(f1ap_du_test_NOT_BUILT f1ap_du_test_NOT_BUILT)
endif()
