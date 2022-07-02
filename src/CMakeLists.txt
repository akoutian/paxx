cmake_minimum_required(VERSION 3.20)

project(pass++ LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(compiler-options)
include(conan-setup)
include(configuration)

add_subdirectory(cli)
add_subdirectory(commands)
add_subdirectory(common)
