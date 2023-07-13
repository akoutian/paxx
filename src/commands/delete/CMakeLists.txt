cmake_minimum_required(VERSION 3.20)

add_library(delete STATIC src/delete.cxx)

target_include_directories(delete PUBLIC include)

target_link_libraries(delete PRIVATE common)
