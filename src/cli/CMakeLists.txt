cmake_minimum_required(VERSION 3.20)

add_library(
  cli STATIC src/args.h src/build-cli.h src/build-cli.cxx src/handle-args.h
             src/handle-args.cxx
)
target_link_libraries(cli PUBLIC common info show bfg::lyra)

add_executable(${PROJECT_NAME} src/main.cxx)
target_link_libraries(${PROJECT_NAME} cli common)

add_pass_test(NAME cli-test SOURCES test/cli-test.cxx)
target_link_libraries(cli-test cli doctest::doctest)
