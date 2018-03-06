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
    vec3 _color = texture(colorTexture, textureUV).rgb;
    color = vec3(1 - _color.x, 1 - _color.y, 1 - _color.z);
}