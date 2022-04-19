cmake_minimum_required(VERSION 3.20)

add_library(find STATIC include/find/find.h src/find.cxx)

target_include_directories(find PUBLIC include)
