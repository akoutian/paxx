cmake_minimum_required(VERSION 3.20)

find_package(clip REQUIRED)
find_package(lyra REQUIRED)
find_package(qr-code-generator REQUIRED)

if(BUILD_TESTING)
    find_package(doctest REQUIRED)
endif()
