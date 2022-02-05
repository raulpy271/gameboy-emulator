
project(game)

add_library(${PROJECT_NAME}
    cpu.cpp
    memory.cpp
    tile.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE utils)

