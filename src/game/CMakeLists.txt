
project(game)

add_library(${PROJECT_NAME}
    cpu.cpp
    cpu_utils.cpp
    game.cpp
    memory.cpp
    tile.cpp
    ppu.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE utils)

