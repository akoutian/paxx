cmake_minimum_required(VERSION 3.20)

add_library(cli STATIC src/build-cli.h src/build-cli.cxx src/handle-args.h src/handle-args.cxx)
target_link_libraries(cli PUBLIC common info show bfg::lyra)

add_executable(${PROJECT_NAME} src/main.cxx)
target_link_libraries(${PROJECT_NAME} cli common)

if(BUILD_TESTING)
    create_test(NAME cli-show-test SOURCES test/cli-show-test.cxx)
    target_link_libraries(cli-show-test cli doctest::doctest)

    create_test(NAME cli-help-test SOURCES test/cli-help-test.cxx)
    target_link_libraries(cli-help-test cli doctest::doctest)

    create_test(NAME cli-version-test SOURCES test/cli-version-test.cxx)
    target_link_libraries(cli-version-test cli doctest::doctest)
endif()
