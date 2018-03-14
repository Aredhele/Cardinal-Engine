#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

uniform float blurPlane;
uniform int   intensity;

void blur(int blurIntensity)
{
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    int middle = blurIntensity / 2;
    for(int u = 0; u < blurIntensity; ++u)
    {
        for(int v = 0; v < blurIntensity; ++v)
        {
            float oX = (u - middle) * offset.x;
            float oY = (v - middle) * offset.y;
            fColor += texture(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb;
        }
    }

    color = fColor / (blurIntensity * blurIntensity);
}

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1f;
    float zFar  = 2000.0f;
    float depth = texture(depthTexture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    float fragmentDepth = texture(depthTexture, textureUV);

    if(fragmentDepth >= blurPlane)
    {
        blur(max(20, (fragmentDepth / (2000 - blurPlane) * 20)));
    }
    else
    {
        color = texture(colorTexture, textureUV);
    }
}