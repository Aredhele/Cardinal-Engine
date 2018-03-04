#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1f;
    float zFar  = 10000.0f;
    float depth = texture2D(depthTexture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    float c = LinearizeDepth(textureUV);
    color = vec3(c, c, c);
}