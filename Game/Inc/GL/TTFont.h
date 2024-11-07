#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "ITexture.h"

/** ���� �۸����Դϴ�. */
struct Glyph
{
	int32_t codePoint;
	glm::ivec2 pos0;
	glm::ivec2 pos1;
	float xoff;
	float yoff;
	float xoff2;
	float yoff2;
	float xadvance;
};