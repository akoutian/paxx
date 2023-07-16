cmake_minimum_required(VERSION 3.20)

project(paxx LANGUAGES CXX)

include(CTest)

include(cmake/compiler-options.cmake)
include(cmake/conan-setup.cmake)
include(cmake/configuration.cmake)
include(cmake/functions.cmake)
include(cmake/system-dependencies.cmake)

add_subdirectory(cli)
add_subdirectory(commands)
add_subdirectory(common)
