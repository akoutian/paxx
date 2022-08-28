cmake_minimum_required(VERSION 3.20)

project(pass++ LANGUAGES CXX)

include(cmake/compiler-options.cmake)
include(cmake/conan-setup.cmake)
include(cmake/configuration.cmake)
include(cmake/functions.cmake)

include(CTest)

add_subdirectory(cli)
add_subdirectory(commands)
add_subdirectory(common)
