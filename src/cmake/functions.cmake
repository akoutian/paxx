# convenience function for creating tests
function(add_pass_test)
  set(opts)
  set(oneValueArgs BIN_NAME)
  set(multiValueArgs BIN_SOURCES)
  cmake_parse_arguments(
    ADD_PASS_TEST "${opts}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}
  )
  add_executable(${ADD_PASS_TEST_BIN_NAME} ${ADD_PASS_TEST_BIN_SOURCES})
  add_test(NAME ${ADD_PASS_TEST_BIN_NAME} COMMAND ${ADD_PASS_TEST_BIN_NAME})
endfunction()
