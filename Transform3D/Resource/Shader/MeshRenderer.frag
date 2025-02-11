#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

uniform sampler2D diffuseMap;

void main()
{
    outFragColor = texture(diffuseMap, inTexCoords);
}