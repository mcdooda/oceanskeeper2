cmake_minimum_required(VERSION 2.6)

project(oceanskeeper2)

file(
    GLOB_RECURSE
    src
    src/*
)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(
    oceanskeeper2
    ${src}
)

target_link_libraries(
    oceanskeeper2
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    lua5.1
    GL
    GLU
    GLEW
)
