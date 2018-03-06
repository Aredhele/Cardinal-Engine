#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform float     quality;
uniform vec3      bloomColor;
uniform int       sampleCount;

void main(void)
{
    const vec2 size = vec2(1600.0f, 900.0f); // Viewport size

    vec3 sum        = vec3(0.0f);
    int  diff       = (sampleCount - 1) / 2;
    vec2 sizeFactor = vec2(1.0f) / size * quality;
    vec3 source     = texture(colorTexture, textureUV).rgb;

    for (int x = -diff; x <= diff; x++)
    {
        for (int y = -diff; y <= diff; y++)
        {
            vec2 offset = vec2(x, y) * sizeFactor;
            sum        += texture(colorTexture, textureUV + offset).rgb;
        }
    }

    color = ((sum / (sampleCount * sampleCount)) + source) * bloomColor;
}