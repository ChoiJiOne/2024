cmake_minimum_required(VERSION 3.27)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(jsoncpp)
add_subdirectory(mimalloc)
add_subdirectory(miniaudio)
add_subdirectory(stb)

set_target_properties(
    glad
    glfw
    glm
    imgui
    jsoncpp
    mimalloc-static
    miniaudio
    stb
    PROPERTIES FOLDER "ThirdParty"
)