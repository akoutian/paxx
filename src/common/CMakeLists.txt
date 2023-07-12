cmake_minimum_required(VERSION 3.20)

add_library(common STATIC src/pgp-decryptor.cxx src/tree-builder.cxx src/tree-writer.cxx)

target_include_directories(common PUBLIC include)

target_link_libraries(common PRIVATE Gpgmepp)

if(BUILD_TESTING)
    create_test(NAME tree-writer-test SOURCES test/tree-writer-test.cxx)
    target_link_libraries(tree-writer-test common doctest::doctest)
endif()
