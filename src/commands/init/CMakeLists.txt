cmake_minimum_required(VERSION 3.20)

add_library(init STATIC include/init/init.h src/init.cxx)

target_include_directories(init PUBLIC include)
