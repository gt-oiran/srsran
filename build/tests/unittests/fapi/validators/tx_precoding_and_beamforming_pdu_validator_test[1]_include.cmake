if(EXISTS "/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/validators/tx_precoding_and_beamforming_pdu_validator_test[1]_tests.cmake")
  include("/home/bezerra/Workspace/srsran/build/tests/unittests/fapi/validators/tx_precoding_and_beamforming_pdu_validator_test[1]_tests.cmake")
else()
  add_test(tx_precoding_and_beamforming_pdu_validator_test_NOT_BUILT tx_precoding_and_beamforming_pdu_validator_test_NOT_BUILT)
endif()
