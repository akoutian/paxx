cmake_minimum_required(VERSION 3.20)

add_library(find STATIC src/find.cxx)

target_include_directories(find PUBLIC include)

target_link_libraries(find PRIVATE common)
