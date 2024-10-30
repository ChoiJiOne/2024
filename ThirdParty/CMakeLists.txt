cmake_minimum_required(VERSION 3.27)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(imgui)

set_target_properties(
    glad
    glfw
    imgui
    PROPERTIES FOLDER "ThirdParty"
)