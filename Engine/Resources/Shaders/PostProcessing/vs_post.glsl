#version 330 core

// In
layout(location = 0) in vec2 v_coord;

// Out
out vec2 f_texcoord;

// Uniform
uniform sampler2D fbo_texture;

void main(void)
{
  gl_Position = vec4(v_coord, 0.0, 1.0);
  f_texcoord  = (v_coord + 1.0) / 2.0;
}