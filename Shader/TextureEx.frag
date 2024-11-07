#version 460 core

layout(location = 0) in vec2 inTexCoords;
layout(location = 1) in vec4 inColor;
layout(location = 2) flat in int inUnit;

layout(location = 0) out vec4 outFragColor;

#define GLYPH_ATLAS_UNIT_0 0
#define GLYPH_ATLAS_UNIT_1 1
#define GLYPH_ATLAS_UNIT_2 2
#define GLYPH_ATLAS_UNIT_3 3
#define GLYPH_ATLAS_UNIT_4 4
#define GLYPH_ATLAS_UNIT_5 5
#define GLYPH_ATLAS_UNIT_6 6
#define GLYPH_ATLAS_UNIT_7 7
#define GLYPH_ATLAS_UNIT_8 8
#define GLYPH_ATLAS_UNIT_9 9

layout(binding = GLYPH_ATLAS_UNIT_0) uniform sampler2D glyphAtlas0;
layout(binding = GLYPH_ATLAS_UNIT_1) uniform sampler2D glyphAtlas1;
layout(binding = GLYPH_ATLAS_UNIT_2) uniform sampler2D glyphAtlas2;
layout(binding = GLYPH_ATLAS_UNIT_3) uniform sampler2D glyphAtlas3;
layout(binding = GLYPH_ATLAS_UNIT_4) uniform sampler2D glyphAtlas4;
layout(binding = GLYPH_ATLAS_UNIT_5) uniform sampler2D glyphAtlas5;
layout(binding = GLYPH_ATLAS_UNIT_6) uniform sampler2D glyphAtlas6;
layout(binding = GLYPH_ATLAS_UNIT_7) uniform sampler2D glyphAtlas7;
layout(binding = GLYPH_ATLAS_UNIT_8) uniform sampler2D glyphAtlas8;
layout(binding = GLYPH_ATLAS_UNIT_9) uniform sampler2D glyphAtlas9;

void main()
{
	vec3 fragColor = inColor.rgb;
	float alpha = 0.0f;

	switch(inUnit)
	{
	case GLYPH_ATLAS_UNIT_0:
		alpha += texture(glyphAtlas0, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_1:
		alpha += texture(glyphAtlas1, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_2:
		alpha += texture(glyphAtlas2, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_3:
		alpha += texture(glyphAtlas3, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_4:
		alpha += texture(glyphAtlas4, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_5:
		alpha += texture(glyphAtlas5, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_6:
		alpha += texture(glyphAtlas6, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_7:
		alpha += texture(glyphAtlas7, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_8:
		alpha += texture(glyphAtlas8, inTexCoords).r;
		break;

	case GLYPH_ATLAS_UNIT_9:
		alpha += texture(glyphAtlas9, inTexCoords).r;
		break;
	}

	outFragColor = vec4(fragColor, alpha);
}