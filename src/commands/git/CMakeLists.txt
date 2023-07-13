cmake_minimum_required(VERSION 3.20)

add_library(git STATIC src/git.cxx)

target_include_directories(git PUBLIC include)

target_link_libraries(git PRIVATE common)
