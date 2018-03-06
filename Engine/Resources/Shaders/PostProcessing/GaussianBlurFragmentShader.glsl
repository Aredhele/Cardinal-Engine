#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform float     intensity;
uniform sampler2D colorTexture;

void main(void)
{
    float g;
    float sum = 0;
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);
    float M[25];
    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float uc = u - 2;
            float vc = v - 2;
            g = exp(-(uc*uc+vc*vc)/(2*intensity*intensity));
            sum += g;
            M[u * 5 + v] = g;
        }
    }

    for(int u = 0; u < 5 ; u++)
    {
        for(int v = 0; v < 5; v++)
        {
            M[u * 5 + v] /= sum;
        }
    }

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += (texture(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb) * M[u * 5 + v];
        }
    }

    color = fColor;
}