#version 460 core

layout(location = 0) out vec4 outFragColor;

uniform vec4 outlineColor;

void main()
{
	outFragColor = outlineColor;
}