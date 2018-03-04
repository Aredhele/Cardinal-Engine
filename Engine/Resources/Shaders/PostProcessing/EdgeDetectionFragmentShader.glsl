#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;

void main(void)
{
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    float M[25] = float[](-1, -1, -1, -1, -1,   -1, -1, -1, -1, -1,  -1, -1, 24, -1, -1,   -1, -1, -1, -1, -1,   -1, -1, -1, -1, -1);

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += (texture2D(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb) * M[u * 5 + v];
        }
    }

    color = fColor / 25;
}