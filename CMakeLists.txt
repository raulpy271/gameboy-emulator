
cmake_minimum_required(VERSION 3.10)

project(gameboy-emulator)

add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE game)

