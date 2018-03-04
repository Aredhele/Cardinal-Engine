#version 330 core

// Out
out vec3 color;

// Uniforms
uniform vec3 fragmentColor;

void main()
{
    color = fragmentColor;
}