cmake_minimum_required(VERSION 3.20)

add_library(rename STATIC include/rename/rename.h src/rename.cxx)

target_include_directories(rename PUBLIC include)

target_link_libraries(rename PRIVATE common)
