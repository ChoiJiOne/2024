#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

layout(binding = 0) uniform sampler2D framebuffer;

uniform bool bHorizontal;

const float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
    float bias = 0.5f;
    vec2 offset = 1.0f / textureSize(framebuffer, 0);
    vec3 fragRGB = texture(framebuffer, inTexCoords).rgb * weight[0];
    float alpha = texture(framebuffer, inTexCoords).a;

    if(bHorizontal)
    {
        for(int index = 1; index < 5; ++index)
        {
            fragRGB += texture(framebuffer, inTexCoords + vec2(offset.x * index * bias, 0.0f)).rgb * weight[index];
            fragRGB += texture(framebuffer, inTexCoords - vec2(offset.x * index * bias, 0.0f)).rgb * weight[index];
        }
    }
    else
    {
        for(int index = 1; index < 5; ++index)
        {
            fragRGB += texture(framebuffer, inTexCoords + vec2(0.0f, offset.y * index * bias)).rgb * weight[index];
            fragRGB += texture(framebuffer, inTexCoords - vec2(0.0f, offset.y * index * bias)).rgb * weight[index];
        }
    }

    outFragColor = vec4(fragRGB, 1.0f);
}