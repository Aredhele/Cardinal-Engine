#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform int       weight;

void main(void)
{
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    float M[9] = float[](0, -1, 0,   0, weight, 0,   0, -1, 0);

    for(int u = 0; u < 3; ++u)
    {
        for(int v = 0; v < 3; ++v)
        {
            float oX = (u - 1) * offset.x;
            float oY = (v - 1) * offset.y;
            fColor += (texture(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb) * M[u * 3 + v];
        }
    }

    color = fColor / (weight - 2);
}