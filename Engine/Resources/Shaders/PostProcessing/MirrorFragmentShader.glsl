#version 330 core

// In
in vec2 f_texcoord;

// Out
out vec3 color;

// Uniform
uniform sampler2D fbo_texture;
uniform sampler2D depth_texture;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1f;
    float zFar  = 10000.0f;
    float depth = texture2D(depth_texture, uv).x;
    return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void)
{
    // X mirror
    vec2 coord = f_texcoord;
    if(f_texcoord.x > 0.5)
    {
        coord.x = 1 - f_texcoord.x;
    }

    color = texture2D(fbo_texture, coord).rgb;

    // Y mirror
    /*vec2 coord = f_texcoord;
    if(f_texcoord.y> 0.5)
    {
      coord.y = 1 - f_texcoord.y;
    }

    color = texture2D(fbo_texture, coord).rgb;*/

    // Box blur
    /*vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += texture2D(fbo_texture, vec2(f_texcoord.x + oX, f_texcoord.y + oY)).rgb;
        }
    }

    color = fColor / 25;*/

    // Edge detection
    /*vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    float M[25] = float[](-1, -1, -1, -1, -1,   -1, -1, -1, -1, -1,  -1, -1, 24, -1, -1,   -1, -1, -1, -1, -1,   -1, -1, -1, -1, -1);

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += (texture2D(fbo_texture, vec2(f_texcoord.x + oX, f_texcoord.y + oY)).rgb) * M[u * 5 + v];
        }
    }

    color = fColor / 25;*/

    // Sharpen
    /*vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);

    float M[25] = float[](0, 0, -1, 0, 0,   0, 0, -1, 0, 0,  -1, -1, 15, -1, -1,   0, 0, -1, 0, 0,   0, 0, -1, 0, 0);

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += (texture2D(fbo_texture, vec2(f_texcoord.x + oX, f_texcoord.y + oY)).rgb) * M[u * 5 + v];
        }
    }

    color = fColor / 25;*/


    // Gaussian blur
    /*float sigma = 1.0f;
    float g;
    float sum = 0;
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);
    float blur_intensity = 5.0f;
    float M[25];

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float uc = u - 2;
            float vc = v - 2;
            g = exp(-(uc*uc+vc*vc)/(2*blur_intensity*blur_intensity));
            sum += g;
            M[u * 5 + v] = g;
        }
    }

    for(int u = 0; u < 5 ; u++)
    {
        for(int v = 0; v < 5; v++)
        {
            M[u * 5 + v] /= sum;
        }
    }

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += (texture2D(fbo_texture, vec2(f_texcoord.x + oX, f_texcoord.y + oY)).rgb) * M[u * 5 + v];
        }
    }

    color = fColor;*/

    // Depth buffer
    /*float c = LinearizeDepth(f_texcoord);
    color = vec3(c, c, c);*/

    // Gods ray

    /*int Samples = 128;
    float Intensity = 0.125, Decay = 0.96875;
    vec2 TexCoord = f_texcoord, Direction = vec2(0.5) - f_texcoord;
    Direction /= Samples;
    vec3 Color = texture2D(fbo_texture, f_texcoord).rgb;

    for(int Sample = 0; Sample < Samples; Sample++)
    {
        Color += texture2D(fbo_texture, TexCoord).rgb * Intensity;
        Intensity *= Decay;
        TexCoord += Direction;
    }

    color = Color;*/



    /*float c = LinearizeDepth(f_texcoord);
    if(c < 0.08)
    {
        c = 0.0f;
    }
    c+=1;
    float sigma = 1.0f;
    float g;
    float sum = 0;
    vec3 fColor = vec3(0.0f, 0.0f, 0.0f);
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);
    float blur_intensity = 1.0f * c;
    float M[25];

    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float uc = u - 2;
            float vc = v - 2;
            g = exp(-(uc*uc+vc*vc)/(2*blur_intensity*blur_intensity));
            sum += g;
            M[u * 5 + v] = g;
        }
    }

    for(int u = 0; u < 5 ; u++)
    {
        for(int v = 0; v < 5; v++)
        {
            M[u * 5 + v] /= sum;
        }
    }



    for(int u = 0; u < 5; ++u)
    {
        for(int v = 0; v < 5; ++v)
        {
            float oX = (u - 2) * offset.x;
            float oY = (v - 2) * offset.y;
            fColor += (texture2D(fbo_texture, vec2(f_texcoord.x + oX, f_texcoord.y + oY)).rgb) * M[u * 5 + v];
        }
    }

   color = fColor;*/
}