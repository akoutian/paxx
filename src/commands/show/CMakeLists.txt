cmake_minimum_required(VERSION 3.20)

add_library(show STATIC include/show/show.h src/show.cxx)

target_include_directories(show PUBLIC include)

target_link_libraries(show common)
