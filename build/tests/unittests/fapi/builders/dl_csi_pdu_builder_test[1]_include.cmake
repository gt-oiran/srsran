if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/builders/dl_csi_pdu_builder_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/builders/dl_csi_pdu_builder_test[1]_tests.cmake")
else()
  add_test(dl_csi_pdu_builder_test_NOT_BUILT dl_csi_pdu_builder_test_NOT_BUILT)
endif()
