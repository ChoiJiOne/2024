cmake_minimum_required(VERSION 3.27)

add_subdirectory(SDL)

set_target_properties(
    SDL_uclibc
    SDL3-shared
    PROPERTIES FOLDER "ThirdParty"
)