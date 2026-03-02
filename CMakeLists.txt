cmake_minimum_required(VERSION 3.10)
project(tetris)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(tetris ${SOURCES})

target_link_libraries(tetris
    ${SDL2_LIBRARIES}
)
