#version 330 core

// In
layout(triangles)                    in;
layout(line_strip, max_vertices = 6) out;

// In
in Vertex
{
  vec4 normal;
  vec4 color;
} vertex[];

// Out
out vec4 vertex_color;

// Uniforms
uniform mat4 PR;
uniform mat4 M;
uniform mat4 V;
uniform mat4 MVP;

void main()
{
  int i;
  for(i = 0; i < gl_in.length(); i++)
  {
    vec3 P = gl_in[i].gl_Position.xyz;
    vec3 N = vertex[i].normal.xyz;

    gl_Position = PR * V * M * vec4(P, 1.0);
    vertex_color = vertex[i].color;
    EmitVertex();

    gl_Position =  PR * V * M * vec4(P + N * 2.0f, 1.0);
    vertex_color = vertex[i].color;
    EmitVertex();

    EndPrimitive();
  }
}