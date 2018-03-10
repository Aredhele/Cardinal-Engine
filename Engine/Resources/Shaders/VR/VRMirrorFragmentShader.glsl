#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D leftEyeTexture;
uniform sampler2D rightEyeTexture;

vec3 textureMultisample(in sampler2DMS sampler, in vec2 texc)
{
    ivec2 ipos  = ivec2(floor(vec2(textureSize(sampler)) * texc));
    vec3 mcolor = vec3(1.0);

    for(int i = 0; i < 2; ++i)
    {
        mcolor += texelFetch(sampler, ipos, i).rgb;
    }

    mcolor /= 4.0;

    return mcolor;
}

void main(void)
{
    if(textureUV.x > 0.5f)
    {
        vec2 tuv = vec2((textureUV.x - 0.5f) * 2.0f, textureUV.y);
        //color = textureMultisample(rightEyeTexture, tuv);
        color = texture(rightEyeTexture, tuv).rgb;
    }
    else
    {
        vec2 tuv = vec2(textureUV.x * 2.0f, textureUV.y);
        //color = textureMultisample(leftEyeTexture, tuv);
        color = texture(leftEyeTexture, tuv).rgb;
    }
}