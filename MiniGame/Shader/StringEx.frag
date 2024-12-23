#version 460 core

layout(location = 0) in vec2 inTexCoords;
layout(location = 1) in vec4 inTextColor;
layout(location = 2) in vec4 inLineColor;
layout(location = 3) flat in int inUnit;

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

void CalculateTextColor(in vec2 texCoords, in vec4 textColor, in vec3 lineColor, out float alpha, inout vec3 fragColor, sampler2D atlas)
{
	ivec2 atlasSize = textureSize(atlas, 0);
	vec2 texelSize = 1.0f / atlasSize;

	alpha = 0.0f;

	alpha += texture(atlas, texCoords + vec2(-texelSize.x,        0.0f)).r;
	alpha += texture(atlas, texCoords + vec2(+texelSize.x,        0.0f)).r;
	alpha += texture(atlas, texCoords + vec2(        0.0f, -texelSize.y)).r;
	alpha += texture(atlas, texCoords + vec2(        0.0f, +texelSize.y)).r;
	alpha += texture(atlas, texCoords + vec2(-texelSize.x, -texelSize.y)).r;
	alpha += texture(atlas, texCoords + vec2(-texelSize.x, +texelSize.y)).r;
	alpha += texture(atlas, texCoords + vec2(+texelSize.x, -texelSize.y)).r;
	alpha += texture(atlas, texCoords + vec2(+texelSize.x, +texelSize.y)).r;

	alpha = min(alpha, 1.0f);
	alpha *= textColor.a;

	fragColor = mix(textColor.rgb, lineColor.rgb, alpha - texture(atlas, texCoords).r);
}

void main()
{
	vec3 fragColor;
	float alpha;

	switch(inUnit)
	{
	case GLYPH_ATLAS_UNIT_0:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas0);
		break;

	case GLYPH_ATLAS_UNIT_1:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas1);
		break;

	case GLYPH_ATLAS_UNIT_2:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas2);
		break;

	case GLYPH_ATLAS_UNIT_3:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas3);
		break;

	case GLYPH_ATLAS_UNIT_4:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas4);
		break;

	case GLYPH_ATLAS_UNIT_5:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas5);
		break;

	case GLYPH_ATLAS_UNIT_6:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas6);
		break;

	case GLYPH_ATLAS_UNIT_7:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas7);
		break;

	case GLYPH_ATLAS_UNIT_8:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas8);
		break;

	case GLYPH_ATLAS_UNIT_9:
		CalculateTextColor(inTexCoords, inTextColor, inLineColor.rgb, alpha, fragColor, glyphAtlas9);
		break;
	}

	outFragColor = vec4(fragColor, alpha);
}