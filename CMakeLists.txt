cmake_minimum_required(VERSION 3.27)

project(HyperCoinDash2D)

set(PROJECT_NAME "HyperCoinDash2D")

add_subdirectory(MiniGame)
add_subdirectory(${PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
