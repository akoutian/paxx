# convenience function for creating tests
function(add_pass_test)
  set(opts)
  set(oneValueArgs NAME)
  set(multiValueArgs SOURCES)
  cmake_parse_arguments(
    ADD_PASS_TEST "${opts}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}
  )
  add_executable(${ADD_PASS_TEST_NAME} ${ADD_PASS_TEST_SOURCES})
  target_include_directories(
    ${ADD_PASS_TEST_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}
  )
  set(doctestArgs "-fc")
  add_test(NAME ${ADD_PASS_TEST_NAME} COMMAND ${ADD_PASS_TEST_NAME}
                                              ${doctestArgs}
  )
endfunction()
