cmake_minimum_required(VERSION 3.20)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(
        DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        TLS_VERIFY ON
        STATUS DOWNLOAD_STATUS
    )

    list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
    list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)

    if(${STATUS_CODE} EQUAL 0)
        message(STATUS "Download completed successfully.")
    else()
        # Exit CMake if the download failed, printing the error message.
        message(FATAL_ERROR "Error occurred during download: ${ERROR_MESSAGE}")
    endif()
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(BUILD_TESTING)
    list(APPEND BUILD_REQUIRES doctest/2.4.8)
endif()

conan_cmake_configure(
    REQUIRES
    dacap-clip/1.5
    lyra/1.6.0
    qr-code-generator/1.8.0
    BUILD_REQUIRES
    ${BUILD_REQUIRES}
    GENERATORS
    cmake_find_package
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

find_package(clip REQUIRED)
find_package(lyra REQUIRED)
find_package(qr-code-generator REQUIRED)

if(BUILD_TESTING)
    find_package(doctest REQUIRED)
endif()
