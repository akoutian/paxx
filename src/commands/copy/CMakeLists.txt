cmake_minimum_required(VERSION 3.20)

add_library(copy STATIC include/copy/copy.h src/copy.cxx)

target_include_directories(copy PUBLIC include)

target_link_libraries(copy PRIVATE common)
