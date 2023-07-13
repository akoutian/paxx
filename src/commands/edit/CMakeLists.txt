cmake_minimum_required(VERSION 3.20)

add_library(edit STATIC src/edit.cxx)

target_include_directories(edit PUBLIC include)

target_link_libraries(edit PRIVATE common)
