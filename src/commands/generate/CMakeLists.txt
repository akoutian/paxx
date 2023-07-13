cmake_minimum_required(VERSION 3.20)

add_library(generate STATIC src/generate.cxx)

target_include_directories(generate PUBLIC include)

target_link_libraries(generate PRIVATE common)
