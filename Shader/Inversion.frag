#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

layout(binding = 0) uniform sampler2D frameBuffer;

void main()
{
	vec3 color = texture(frameBuffer, inTexCoords).rgb;
	outFragColor =  vec4(1.0f - color, 1.0f);
}