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
    float zFar  = 2000.0f;
    float depth = texture(depthTexture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    float c = LinearizeDepth(textureUV);
    // float c = texture(depthTexture, textureUV).r;
    color = vec3(c, c, c);
}