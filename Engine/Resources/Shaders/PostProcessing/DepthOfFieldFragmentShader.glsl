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

    if(fragmentDepth >= (blurPlane / 2000.0f))
    {
         vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
         vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

         int middle = intensity / 2;
         for(int u = 0; u < intensity; ++u)
         {
             for(int v = 0; v < intensity; ++v)
             {
                 float oX = (u - middle) * offset.x;
                 float oY = (v - middle) * offset.y;
                 fColor += texture(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb;
             }
         }

         color = fColor / (intensity * intensity);
    }
    else
    {
        color = texture(colorTexture, textureUV).rgb;
    }
}