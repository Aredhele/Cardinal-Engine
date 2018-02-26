#version 330 core

// In
in vec2 uv;
in vec3 light_vector;
in vec3 vertex_world;
in vec3 surface_normal;

struct PointLightOut
{
   float point_light_range;
   float point_light_intensity;
   vec3  point_light_vector;
   vec3  point_light_color;
   vec3  point_light_pos;
};

in PointLightOut lights_out[4];

// Out
out vec3 color;

// Uniforms
uniform sampler2D textureSampler;

uniform vec3  lightPosition;
uniform float lightIntensity;
uniform float ambientIntensity;
uniform vec3  lightColor;
uniform int   lightCount;

void main(void)
{
    vec3  diffuse = texture(textureSampler, uv).rgb;

    vec3 n = normalize(surface_normal);
    vec3 l = normalize(light_vector);

    float brightness    = clamp(dot(n, l), 0.0f, 1.0f);
    vec3  worldLighting = ambientIntensity * diffuse * lightIntensity + diffuse * lightColor * lightIntensity * brightness;

    float _distance     = 0.0f;
    float _brightness   = 0.0f;
    float _intensity    = 0.0f;
    vec3  _lightColor   = vec3(0.0f);
    vec3  pointLighting = vec3(0.0f);

    for(int i = 0; i < lightCount; ++i)
    {
        l         = normalize(lights_out[i].point_light_vector);
        _distance = length   (lights_out[i].point_light_vector);

        if(_distance <= lights_out[i].point_light_range)
        {
            _brightness += max(0.0f, (max(dot(n, l), 1.0f)) * pow(smoothstep(lights_out[i].point_light_range, 0.1f, _distance), 1.0f));
        }

        _lightColor += lights_out[i].point_light_color;
        _intensity  += lights_out[i].point_light_intensity / 5.0f;
    }

    pointLighting = diffuse * _lightColor * _intensity * _brightness;

    if(lightCount > 1)
    {
        pointLighting /= lightCount;
    }

    color = worldLighting + pointLighting;
}