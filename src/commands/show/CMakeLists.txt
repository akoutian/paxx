cmake_minimum_required(VERSION 3.20)

add_library(
    show STATIC
    include/show/show.h
    src/show-tree.cxx
    src/show-tree.h
    src/show.cxx
    src/symbols.h
    src/tree-writer.cxx
    src/tree-writer.h
)

target_include_directories(show PUBLIC include)

target_link_libraries(show common)

if(BUILD_TESTING)
    add_pass_test(NAME show-test SOURCES test/tree-writer-test.cxx)
    target_link_libraries(show-test show doctest::doctest)
endif()
