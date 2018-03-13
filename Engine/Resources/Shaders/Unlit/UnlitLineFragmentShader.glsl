#version 330 core

// Out
out vec3 color;

// Uniform
uniform vec3 lineColor;

void main()
{
    color = lineColor;
}