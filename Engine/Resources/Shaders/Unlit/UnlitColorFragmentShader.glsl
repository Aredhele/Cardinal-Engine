#version 330 core

// In
in vec3 fragmentColor;

// Out
out vec3 color;

void main()
{
    color = fragmentColor;
}