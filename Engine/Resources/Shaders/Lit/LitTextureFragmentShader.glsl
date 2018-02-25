#version 330 core

// In
in vec2 uv;
in vec3 light_vector;
in vec3 vertex_world;
in vec3 surface_normal;

// Out
out vec3 color;

// Uniforms
uniform sampler2D textureSampler;

uniform vec3  lightDirection;
uniform float lightIntensity;
uniform float ambientIntensity;
uniform vec3  lightColor;

void main(void)
{
     vec3  diffuse = texture(textureSampler, uv).rgb;

     vec3 n = normalize(surface_normal);
     vec3 l = normalize(light_vector);

     float brightness = clamp(dot(n, l), 0.0f, 1.0f);
     color = ambientIntensity * diffuse + diffuse * lightColor * lightIntensity * brightness;
}