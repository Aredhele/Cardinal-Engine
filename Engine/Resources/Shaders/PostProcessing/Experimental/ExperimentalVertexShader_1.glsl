#version 330 core

// In
layout(location = 0) in vec2 vertexCoord;

// Out
out vec2 textureUV;

uniform float RAND_MAX = 43758.5453f;

// Simple pseudo-random
float rand(vec2 v2_seed)
{
    return fract(sin(dot(v2_seed.xy ,vec2(12.9898,78.233))) * RAND_MAX);
}

// Does nothing
void noop()
{
    // Position
    gl_Position = vec4(vertexCoord, 0.0, 1.0);

    // Texture UV
    textureUV   = (vertexCoord + 1.0) / 2.0;
}

void main(void)
{
    // Position
    gl_Position = vec4(0,0,0, 1.0);
    
    // Texture UV
    textureUV   = (vertexCoord + 1.0) / 2.0;
}