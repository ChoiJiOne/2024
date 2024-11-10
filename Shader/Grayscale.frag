#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

layout(binding = 0) uniform sampler2D frameBuffer;

void main()
{
	vec3 color = texture(frameBuffer, inTexCoords).rgb;
	float grayscale = dot(color, vec3(0.2126f, 0.7152f, 0.0722f));
	outFragColor =  vec4(grayscale, grayscale, grayscale, 1.0f);
}