cmake_minimum_required(VERSION 3.20)

add_library(
  show STATIC include/show/show.h src/tree.h src/tree.cxx src/show.cxx
              src/types.h
)

target_include_directories(show PUBLIC include)

target_link_libraries(show common)

add_executable(show-test test/tree-test.cxx)

target_link_libraries(show-test show doctest::doctest)
