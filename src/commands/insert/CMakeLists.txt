cmake_minimum_required(VERSION 3.20)

add_library(insert STATIC include/insert/insert.h src/insert.cxx)

target_include_directories(insert PUBLIC include)
