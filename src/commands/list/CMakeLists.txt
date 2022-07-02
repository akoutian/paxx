cmake_minimum_required(VERSION 3.20)

add_library(list STATIC include/list/list.h src/list.cxx)

target_include_directories(list PUBLIC include)

target_link_libraries(list common)
