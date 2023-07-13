cmake_minimum_required(VERSION 3.20)

add_library(init STATIC src/init.cxx)

target_include_directories(init PUBLIC include)

target_link_libraries(init PRIVATE common)
