cmake_minimum_required(VERSION 3.27)

add_subdirectory(glad)
add_subdirectory(glfw)

set_target_properties(
    glad
    glfw
    PROPERTIES FOLDER "ThirdParty"
)