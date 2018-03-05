#version 330 core

// In
layout(location = 0) in vec2 vertexCoord;

// Out
out vec2 textureUV;

void main(void)
{
  gl_Position = vec4(vertexCoord, 0.0, 1.0);
  textureUV   = (vertexCoord + 1.0) / 2.0;
}