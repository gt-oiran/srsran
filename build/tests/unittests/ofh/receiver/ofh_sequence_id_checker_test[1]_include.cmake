if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/ofh/receiver/ofh_sequence_id_checker_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/ofh/receiver/ofh_sequence_id_checker_test[1]_tests.cmake")
else()
  add_test(ofh_sequence_id_checker_test_NOT_BUILT ofh_sequence_id_checker_test_NOT_BUILT)
endif()
