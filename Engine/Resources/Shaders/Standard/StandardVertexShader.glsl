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

struct PointLightOut
{
   float point_light_range;
   float point_light_intensity;
   vec3  point_light_vector;
   vec3  point_light_color;
   vec3  point_light_pos;
};

out PointLightOut lights_out[4];

// Uniforms
uniform mat4 M;
uniform mat4 V;
uniform mat4 MVP;
uniform vec3 lightDirection;

// Lighting
struct PointLight
{
    float range;
    float intensity;
    vec3  color;
    vec3  position;
};

uniform int        lightCount;
uniform PointLight lights[4];

void main()
{
    gl_Position    = MVP * vec4(vertex_position, 1.0f);
    vertex_world   = (M  * vec4(vertex_position, 1.0f)).xyz;

    vec3 vertexPosition_cameraspace = (V * M * vec4(vertex_position, 1.0f)).xyz;
    light_vector = -(vec4(lightDirection, 1.0f)).xyz;

    surface_normal = (M * vec4(vertex_normal, 0.0f)).xyz;
    uv             = vertex_uv;

    if(lightCount > 0)
    {
        lights_out[0].point_light_range     = lights[0].range;
        lights_out[0].point_light_intensity = lights[0].intensity;
        lights_out[0].point_light_color     = lights[0].color;
        lights_out[0].point_light_pos       = lights[0].position;
        lights_out[0].point_light_vector    = lights[0].position - vertex_world;
    }

    if(lightCount > 1)
    {
        lights_out[1].point_light_range     = lights[1].range;
        lights_out[1].point_light_intensity = lights[1].intensity;
        lights_out[1].point_light_color     = lights[1].color;
        lights_out[1].point_light_pos       = lights[1].position;
        lights_out[1].point_light_vector    = lights[1].position - vertex_world;
     }

    if(lightCount > 2)
    {
        lights_out[2].point_light_range     = lights[2].range;
        lights_out[2].point_light_intensity = lights[2].intensity;
        lights_out[2].point_light_color     = lights[2].color;
        lights_out[2].point_light_pos       = lights[2].position;
        lights_out[2].point_light_vector    = lights[2].position - vertex_world;
    }

    if(lightCount > 3)
    {
        lights_out[3].point_light_range     = lights[3].range;
        lights_out[3].point_light_intensity = lights[3].intensity;
        lights_out[3].point_light_color     = lights[3].color;
        lights_out[3].point_light_pos       = lights[3].position;
        lights_out[3].point_light_vector    = lights[3].position - vertex_world;
    }
}