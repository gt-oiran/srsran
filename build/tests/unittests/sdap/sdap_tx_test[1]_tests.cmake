add_test( sdap_tx_test.create_new_entity /home/bezerra/Workspace/srsran/build/tests/unittests/sdap/sdap_tx_test [==[--gtest_filter=sdap_tx_test.create_new_entity]==] --gtest_also_run_disabled_tests)
set_tests_properties( sdap_tx_test.create_new_entity PROPERTIES WORKING_DIRECTORY /home/bezerra/Workspace/srsran/build/tests/unittests/sdap SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( sdap_tx_test.test_tx /home/bezerra/Workspace/srsran/build/tests/unittests/sdap/sdap_tx_test [==[--gtest_filter=sdap_tx_test.test_tx]==] --gtest_also_run_disabled_tests)
set_tests_properties( sdap_tx_test.test_tx PROPERTIES WORKING_DIRECTORY /home/bezerra/Workspace/srsran/build/tests/unittests/sdap SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( sdap_tx_test_TESTS sdap_tx_test.create_new_entity sdap_tx_test.test_tx)
