#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

layout(binding = 0) uniform sampler2D frameBuffer;

layout(binding = 0) uniform _BlendColor
{
	vec4 color;
} BlendColor;

void main()
{
	vec3 color = mix(texture(frameBuffer, inTexCoords).rgb, BlendColor.color.rgb, BlendColor.color.a);
	outFragColor =  vec4(color, 1.0f);
}