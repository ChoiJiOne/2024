#version 460 core

layout(location = 0) in vec2 inTexCoords;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 outFragColor;
layout(location = 1) out vec4 outBrightColor;

layout(binding = 0) uniform sampler2D glyphAtlasMap;

void main()
{
	vec3 fragColor = inColor.rgb;
	float alpha = inColor.a * texture(glyphAtlasMap, inTexCoords).r;
	outFragColor = vec4(fragColor, alpha);

	float brightness = dot(fragColor, vec3(0.2126f, 0.7152f, 0.0722f));
	if(brightness > 1.0f)
	{
		outBrightColor = vec4(fragColor, alpha);
	}
	else
	{
		outBrightColor = vec4(0.0f, 0.0f, 0.0f, alpha);
	}
}