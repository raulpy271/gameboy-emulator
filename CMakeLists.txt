
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


if(NOT DEFINED ENV{test_setup})
    message("No tests")
    add_subdirectory(src/gui)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
    add_executable(main main.cpp)
    target_link_libraries(main PRIVATE game gui)
    target_link_libraries(main PRIVATE ${GTKMM_LIBRARIES})
    target_include_directories(main PRIVATE ${GTKMM_INCLUDE_DIRS})
    target_link_directories(main PRIVATE ${GTKMM_LIBRARY_DIRS})
    target_compile_options(main PRIVATE ${GTKMM_CFLAGS_OTHER})

    add_executable(debug debug_code.cpp)
    target_link_libraries(debug PRIVATE game utils)
else()
    message("Test building")
endif()


