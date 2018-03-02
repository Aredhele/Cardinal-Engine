#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

void main(void)
{
    // X mirror
    vec2 coord = textureUV;
    if(coord.x > 0.5)
    {
        coord.x = 1 - coord.x;
    }

    color = texture2D(colorTexture, coord).rgb;
}