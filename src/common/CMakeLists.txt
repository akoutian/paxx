cmake_minimum_required(VERSION 3.20)

add_library(common INTERFACE include/common/types.h)

target_include_directories(common INTERFACE include)
