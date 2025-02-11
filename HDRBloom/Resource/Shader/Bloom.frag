#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

layout(binding = 0) uniform sampler2D scene;
layout(binding = 1) uniform sampler2D blur;

const float gamma = 2.2f;
const float exposure = 1.0f;

void main()
{
    vec3 sceneColor = texture(scene, inTexCoords).rgb;
    vec3 blurColor = texture(blur, inTexCoords).rgb;

    sceneColor += blurColor;
    vec3 fragColor = vec3(1.0f) - exp(-sceneColor * exposure);
    fragColor = pow(fragColor, vec3(1.0f / gamma));

    outFragColor = vec4(fragColor, 1.0);
}