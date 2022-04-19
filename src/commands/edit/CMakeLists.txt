cmake_minimum_required(VERSION 3.20)

add_library(edit STATIC include/edit/edit.h src/edit.cxx)

target_include_directories(edit PUBLIC include)
