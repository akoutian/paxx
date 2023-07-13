cmake_minimum_required(VERSION 3.20)

add_library(grep STATIC include/grep/grep.h src/grep.cxx)

target_include_directories(grep PUBLIC include)

target_link_libraries(grep PRIVATE common)
