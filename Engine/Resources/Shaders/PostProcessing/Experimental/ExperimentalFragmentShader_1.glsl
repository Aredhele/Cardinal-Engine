#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;

void main(void)
{
  color = texture(colorTexture, textureUV).rgb;
}