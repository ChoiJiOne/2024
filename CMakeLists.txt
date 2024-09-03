cmake_minimum_required(VERSION 3.27)

project(Runner2D)

set(PROJECT_NAME "Runner2D")

add_subdirectory(GameMaker)
add_subdirectory(${PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
