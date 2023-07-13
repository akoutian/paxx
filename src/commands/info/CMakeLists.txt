cmake_minimum_required(VERSION 3.20)

add_library(info STATIC src/info.cxx)

target_include_directories(info PUBLIC include)

target_link_libraries(info PRIVATE common)
