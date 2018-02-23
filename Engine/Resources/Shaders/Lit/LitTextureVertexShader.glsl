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
uniform vec3 lightPosition;

void main()
{
    gl_Position    = MVP * vec4(vertex_position, 1.0f);
    vertex_world   = (M  * vec4(vertex_position, 1.0f)).xyz;

    vec3 vertexPosition_cameraspace = (V * M * vec4(vertex_position, 1.0f)).xyz;

    vec3 LightPosition_cameraspace = (V * vec4(lightPosition, 1.0f)).xyz;
    light_vector = LightPosition_cameraspace + (vec3(0.0f, 0.0f, 0.0f) - vertexPosition_cameraspace);

    surface_normal = (V * M * vec4(vertex_normal, 0.0f)).xyz;
    uv             = vertex_uv;
}