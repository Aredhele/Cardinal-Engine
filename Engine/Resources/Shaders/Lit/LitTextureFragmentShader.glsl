#version 330 core

// In
in vec2 UV;

// Out
out vec3 color;

// Uniforms
uniform sampler2D textureSampler;

void main()
{
    color = texture(textureSampler, UV).rgb;
}