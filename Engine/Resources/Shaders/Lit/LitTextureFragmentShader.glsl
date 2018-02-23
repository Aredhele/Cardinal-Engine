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

void main(void)
{
     float AmbientLevel         = 5.0f;
     float LightPower           = 0.4f;
     vec3  LightColor           = vec3(1.0f, 1.0f, 1.0f);
     vec3  MaterialDiffuseColor = texture(textureSampler, uv).rgb;
     vec3  MaterialAmbientColor = vec3(0.1f, 0.1f, 0.1f) * MaterialDiffuseColor;

     vec3 n = normalize(surface_normal);
     vec3 l = normalize(light_vector);

     float brightness = clamp(dot(n, l), 0.0f, 1.0f);
     color = AmbientLevel * MaterialAmbientColor + (MaterialDiffuseColor * LightColor * LightPower * brightness);
}