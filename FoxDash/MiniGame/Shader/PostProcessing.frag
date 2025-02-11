#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outFragColor;

layout(binding = 0) uniform sampler2D frameBuffer;

layout(binding = 0) uniform _PerFrameUBO
{
	vec4 color;
	int type;
} PerFrameUBO;

#define TYPE_BLIT          0
#define TYPE_BLEND_COLOR   1
#define TYPE_INVERSION     2
#define TYPE_GRAYSCALE     3
#define TYPE_GAUSSIAN_BLUR 4

#define pow2(x) (x * x)

const float pi = atan(1.0) * 4.0;
const int samples = 35;
const float sigma = float(samples) * 0.25;

float Gaussian(vec2 offset) 
{
    return 1.0f / (2.0f * pi * pow2(sigma)) * exp(-((pow2(offset.x) + pow2(offset.y)) / (2.0f * pow2(sigma))));
}

// Single Pass Gaussian Blur: https://www.shadertoy.com/view/4tSyzy
vec3 Blur(sampler2D fb, vec2 texCoord, vec2 scale) 
{
    vec3 col = vec3(0.0f);
    float accum = 0.0f;
    float weight;
    vec2 offset;
    
    for (int x = -samples / 2; x < samples / 2; ++x) 
    {
        for (int y = -samples / 2; y < samples / 2; ++y) 
        {
            offset = vec2(x, y);
            weight = Gaussian(offset);
            col += texture(fb, texCoord + scale * offset).rgb * weight;
            accum += weight;
        }
    }
    
    return col / accum;
}

void main()
{
	vec3 color;

	switch(PerFrameUBO.type)
	{
	case TYPE_BLIT:
		outFragColor = vec4(texture(frameBuffer, inTexCoords).rgb, 1.0f);
		break;

	case TYPE_BLEND_COLOR:
		color = mix(texture(frameBuffer, inTexCoords).rgb, PerFrameUBO.color.rgb, PerFrameUBO.color.a);
		outFragColor =  vec4(color, 1.0f);
		break;

	case TYPE_INVERSION:
		color = texture(frameBuffer, inTexCoords).rgb;
		outFragColor =  vec4(1.0f - color, 1.0f);
		break;

	case TYPE_GRAYSCALE:
		color = texture(frameBuffer, inTexCoords).rgb;
		float grayscale = dot(color, vec3(0.2126f, 0.7152f, 0.0722f));
		outFragColor =  vec4(grayscale, grayscale, grayscale, 1.0f);
	    break;

	case TYPE_GAUSSIAN_BLUR:
		ivec2 size = textureSize(frameBuffer, 0);
		vec2 scale = 1.0f / size;
		color = Blur(frameBuffer, inTexCoords, scale);
		outFragColor =  vec4(color.rgb, 1.0f);
		break;
	}
}