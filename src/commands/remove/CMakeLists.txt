cmake_minimum_required(VERSION 3.20)

add_library(remove STATIC src/remove.cxx)

target_include_directories(remove PUBLIC include)

target_link_libraries(remove PRIVATE common)
