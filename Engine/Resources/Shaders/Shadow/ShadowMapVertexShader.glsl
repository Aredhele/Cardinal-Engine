#version 330 core

// In
layout(location = 0) in vec3 vertexCoord;

// Uniforms
uniform mat4 depthMVP;

void main()
{
    gl_Position =  depthMVP * vec4(vertexCoord, 1);
}