cmake_minimum_required(VERSION 3.20)

add_library(generate STATIC include/generate/generate.h src/generate.cxx)

target_include_directories(generate PUBLIC include)
