cmake_minimum_required(VERSION 3.20)

if(BUILD_TESTING)
    list(APPEND CONAN_BUILD_REQUIRES doctest/2.4.8)
endif()

list(APPEND CONAN_REQUIRES dacap-clip/1.5 lyra/1.6.0 qr-code-generator/1.8.0)
