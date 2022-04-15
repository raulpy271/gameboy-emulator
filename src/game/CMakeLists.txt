
project(game)

add_library(${PROJECT_NAME}
    cpu/cpu.cpp
    cpu/cpu_instructions.cpp
    cpu/cpu_prefixed_instructions.cpp
    cpu/cpu_utils.cpp
    cpu/interrupts.cpp
    game.cpp
    memory.cpp
    tile.cpp
    ppu.cpp
    palette.cpp
    timer_registers.cpp
    keypad.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE utils)

