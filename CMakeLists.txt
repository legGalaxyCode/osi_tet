cmake_minimum_required(VERSION 3.17)
project(tetris)

set(CMAKE_CXX_STANDARD 17)
#set(SFML_DIR "C:/Program Files/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
add_executable(tetris main.cpp button.cpp button.h world.cpp world.h tetris.cpp tetris.h text_block.cpp text_block.h credits.cpp credits.h)
target_link_libraries(tetris sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
