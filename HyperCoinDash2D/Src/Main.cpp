#include <iostream>

#include <SDL3/SDL.h>

#include <ft2build.h>
#include FT_FREETYPE_H

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}


    SDL_Quit();
    return 0;
}