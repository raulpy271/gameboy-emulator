
cmake_minimum_required(VERSION 3.10)

project(gameboy-emulator)

add_subdirectory(src)
add_subdirectory(tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE game)

