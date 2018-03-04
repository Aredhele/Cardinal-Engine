#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1f;
    float zFar  = 10000.0f;
    float depth = texture2D(depthTexture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    int Samples = 128;
    float Intensity = 0.125, Decay = 0.96875;
    vec2 TexCoord = textureUV, Direction = vec2(0.5) - textureUV;
    Direction /= Samples;
    vec3 Color = texture2D(colorTexture, textureUV).rgb;

    for(int Sample = 0; Sample < Samples; Sample++)
    {
        Color += texture2D(colorTexture, TexCoord).rgb * Intensity;
        Intensity *= Decay;
        TexCoord += Direction;
    }

    color = Color;
}