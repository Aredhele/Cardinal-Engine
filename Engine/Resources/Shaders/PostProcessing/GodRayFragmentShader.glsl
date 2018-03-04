#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

uniform float     decay;
uniform float     intensity;
uniform int       sampleCount;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1f;
    float zFar  = 10000.0f;
    float depth = texture2D(depthTexture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    vec2 TexCoord = textureUV, Direction = vec2(0.5) - textureUV;
    Direction /= sampleCount;
    vec3 Color = texture2D(colorTexture, textureUV).rgb;

    float _intensity = intensity;
    for(int Sample = 0; Sample < sampleCount; Sample++)
    {
        Color += texture2D(colorTexture, TexCoord).rgb * _intensity;
        _intensity *= decay;
        TexCoord += Direction;
    }

    color = Color;
}