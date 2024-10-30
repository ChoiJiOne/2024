cmake_minimum_required(VERSION 3.27)

add_subdirectory(freetype)
add_subdirectory(SDL)
add_subdirectory(zlib)

set_target_properties(
    SDL_uclibc
    SDL3-shared
    freetype
    zlib
    zlibstatic
    PROPERTIES FOLDER "ThirdParty"
)