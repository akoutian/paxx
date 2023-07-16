cmake_minimum_required(VERSION 3.20)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
         "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON
    )
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(BUILD_TESTING)
    list(APPEND BUILD_REQUIRES doctest/2.4.8)
endif()

conan_cmake_configure(
    REQUIRES lyra/1.6.0 BUILD_REQUIRES ${BUILD_REQUIRES} GENERATORS cmake_find_package
)

conan_cmake_autodetect(settings)

conan_cmake_install(
    PATH_OR_REFERENCE
    .
    BUILD
    missing
    REMOTE
    conancenter
    SETTINGS
    ${settings}
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(lyra REQUIRED)

if(BUILD_TESTING)
    find_package(doctest REQUIRED)
endif()
