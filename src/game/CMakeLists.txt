
project(game)

add_library(${PROJECT_NAME}
    cpu/cpu.cpp
    cpu/cpu_instructions.cpp
    cpu/cpu_prefixed_instructions.cpp
    cpu/cpu_utils.cpp
    cpu/instructions_size.cpp
    cpu/interrupts.cpp
    game.cpp
    memory.cpp
    ppu.cpp
    palette.cpp
    timer_registers.cpp
    keypad.cpp
    LCDC.cpp
    STAT.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE utils)

