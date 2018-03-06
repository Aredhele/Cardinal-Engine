#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;
uniform bool      bMirrorX;
uniform bool      bMirrorY;

void main(void)
{
    vec2 coord = textureUV;
    if(bMirrorX && coord.x > 0.5) coord.x = 1 - coord.x;
    if(bMirrorY && coord.y > 0.5) coord.y = 1 - coord.y;

    color = texture(colorTexture, coord).rgb;
}