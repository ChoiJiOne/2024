#version 460 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoords;
layout(location = 2) in vec4 inColor;
layout(location = 4) in int inUnit;
layout(location = 5) in float inTransparent;

layout(location = 0) out vec2 outTexCoords;
layout(location = 1) out vec4 outColor;
layout(location = 2) out int outUnit;
layout(location = 3) out float outTransparent;

layout(binding = 0) uniform _PerFrameUBO
{
	mat4 ortho;
} PerFrameUBO;

uniform mat4 ortho;

void main()
{
	gl_Position = PerFrameUBO.ortho * vec4(vec3(inPosition, 0.0f), 1.0f);
	outTexCoords = vec2(inTexCoords.x, inTexCoords.y);
	outColor = inColor;
	outUnit = inUnit;
	outTransparent = inTransparent;
}