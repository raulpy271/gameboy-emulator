
project(unit_tests)

enable_testing()

add_executable(unit_test 
  unit_test.cpp
  memory.cpp
  prefixed_instructions.cpp
  initialize_registers.cpp
  utils.cpp
  interrupts.cpp
  palette.cpp
  timer_registers.cpp
  keypad.cpp
  ppu.cpp
)

target_link_libraries(unit_test 
  gtest_main
  game
  utils
)

include(GoogleTest)

gtest_discover_tests(unit_test)

