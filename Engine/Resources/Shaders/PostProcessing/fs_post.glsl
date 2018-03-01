#version 330 core

// In
in vec2 f_texcoord;

// Out
out vec3 color;

// Uniform
uniform sampler2D fbo_texture;

void main(void)
{
  color = texture2D(fbo_texture, f_texcoord).rgb;
}