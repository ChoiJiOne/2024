cmake_minimum_required(VERSION 3.27)

add_subdirectory(freetype)
add_subdirectory(SDL)

set_target_properties(
    SDL_uclibc
    SDL3-shared
    freetype
    PROPERTIES FOLDER "ThirdParty"
)