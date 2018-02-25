#version 330 core

// In
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_uv;

// Out
out vec2 uv;
out vec3 light_vector;
out vec3 vertex_world;
out vec3 surface_normal;

// Uniforms
uniform mat4 M;
uniform mat4 V;
uniform mat4 MVP;
uniform vec3 lightDirection;

void main()
{
    gl_Position    = MVP * vec4(vertex_position, 1.0f);
    vertex_world   = (M  * vec4(vertex_position, 1.0f)).xyz;

    vec3 vertexPosition_cameraspace = (V * M * vec4(vertex_position, 1.0f)).xyz;
    light_vector = -(vec4(lightDirection, 1.0f)).xyz;

    surface_normal = (M * vec4(vertex_normal, 0.0f)).xyz;
    uv             = vertex_uv;
}