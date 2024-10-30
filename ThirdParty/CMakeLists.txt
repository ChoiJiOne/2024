cmake_minimum_required(VERSION 3.27)

add_subdirectory(glfw)

set_target_properties(
    glfw
    PROPERTIES FOLDER "ThirdParty"
)