#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D depthTexture;
uniform sampler2D lightScatteringTexture;

uniform float decay;
uniform float weight;
uniform float density;
uniform float exposure;
uniform int   sampleCount;
uniform vec2  lightPosition2D;

void main(void)
{
    float illuminationDecay = 1.0f;

    vec2 tc  = textureUV;
    vec2 deltaTexCoord = tc - lightPosition2D;
    deltaTexCoord *= 1.0 / float(sampleCount) * density;

    vec3 _color = texture(lightScatteringTexture, tc.xy).xyz * 0.4;

    for(int i=0; i < sampleCount ; i++)
    {
        tc -= deltaTexCoord;
        vec3 sampleX = texture(lightScatteringTexture, tc).xyz * 0.4;
        sampleX *= illuminationDecay * weight;
        _color += sampleX;
        illuminationDecay *= decay;
    }

    vec3 c = texture(colorTexture, textureUV).rgb;
    color = _color + c;
}