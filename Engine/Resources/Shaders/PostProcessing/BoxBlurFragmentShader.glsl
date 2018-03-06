#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform int       intensity;

void main(void)
{
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    int middle = intensity / 2;
    for(int u = 0; u < intensity; ++u)
    {
        for(int v = 0; v < intensity; ++v)
        {
            float oX = (u - middle) * offset.x;
            float oY = (v - middle) * offset.y;
            fColor += texture(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb;
        }
    }

    color = fColor / (intensity * intensity);
}