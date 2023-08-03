cmake_minimum_required(VERSION 3.20)

add_library(show STATIC src/show.cxx src/qr.cxx)

target_include_directories(show PUBLIC include)

target_link_libraries(show PRIVATE qr-code-generator::qr-code-generator clip::clip common)
