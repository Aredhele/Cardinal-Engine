#version 330 core

in vec2 UV;
out vec4 color;
uniform sampler2D myTextureSampler;

void main()
{
    float a = 1.0f;
    vec3 rgb = texture(myTextureSampler, UV).rgb;
    if(rgb.x == 1.0f && rgb.y == 1.0f && rgb.z == 1.0f)
    {
        discard;
    }

    color = texture(myTextureSampler, UV).rgba;
    color.a = a;
}