cmake_minimum_required(VERSION 3.20)

add_library(git STATIC include/git/git.h src/git.cxx)

target_include_directories(git PUBLIC include)

target_link_libraries(git common)
