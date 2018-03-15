#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

uniform vec3  fogColor;
uniform float fogDensity;

// Constants
const float LOG2 = 1.442695f;

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
    vec4 colorBuffer    = texture(colorTexture, textureUV);
    vec4 fogColor       = vec4(fogColor.x, fogColor.y, fogColor.z, 1.0f);

    float fogFactor = exp2(-fogDensity * fogDensity * fragmentDepth * fragmentDepth * LOG2);
    fogFactor       = clamp(fogFactor, 0.0f, 1.0f);
    color           = mix(fogColor, colorBuffer, fogFactor ).rgb;
}