#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

uniform float fogDistance;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1f;
    float zFar  = 2000.0f;
    float depth = texture(depthTexture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    float fragmentDepth = LinearizeDepth(textureUV);

    if(fragmentDepth >= (fogDistance / 2000.0f))
    {
         vec3 fogColor = vec3(0.7f, 0.7f, 0.7f);
         color = fColor / (intensity * intensity);
         color += fogColor;
         color /= 2;
    }
    else
    {
        color = texture(colorTexture, textureUV).rgb;
    }
}