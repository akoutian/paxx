cmake_minimum_required(VERSION 3.20)

add_library(cli STATIC src/build-cli.cxx src/handle-args.cxx src/cli.cxx)
target_link_libraries(cli PRIVATE common info show remove bfg::lyra)

add_executable(${PROJECT_NAME} src/main.cxx)
target_link_libraries(${PROJECT_NAME} cli common bfg::lyra)

if(BUILD_TESTING)
    create_test(NAME cli-show-test SOURCES test/cli-show-test.cxx)
    target_link_libraries(cli-show-test common cli doctest::doctest bfg::lyra)

    create_test(NAME cli-help-test SOURCES test/cli-help-test.cxx)
    target_link_libraries(cli-help-test common cli doctest::doctest bfg::lyra)

    create_test(NAME cli-version-test SOURCES test/cli-version-test.cxx)
    target_link_libraries(cli-version-test common cli doctest::doctest bfg::lyra)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
