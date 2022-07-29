cmake_minimum_required(VERSION 3.20)

add_executable(${PROJECT_NAME} src/args.h src/main.cxx)

target_link_libraries(${PROJECT_NAME} common info show bfg::lyra)
