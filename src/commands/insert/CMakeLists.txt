cmake_minimum_required(VERSION 3.20)

add_library(insert STATIC src/insert.cxx)

target_include_directories(insert PUBLIC include)

target_link_libraries(insert PRIVATE common)
