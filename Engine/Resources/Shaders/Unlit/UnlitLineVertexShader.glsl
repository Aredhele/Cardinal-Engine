#version 330 core

// In
layout(location = 0) in vec3 vertex;

// Uniforms
uniform mat4 MVP;

void main()
{
    gl_Position   =  MVP * vec4(vertex, 1.0f);
}
