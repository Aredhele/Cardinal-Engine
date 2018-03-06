#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform float     threshold;
uniform vec3      tone;

void main(void)
{
    // Fragment gray scale
    vec3 _color = texture(colorTexture, textureUV).rgb;
    float gray = dot(_color, vec3(0.299, 0.587, 0.114));

    if(gray < threshold)
    {
        float divide = gray / threshold;
        color.x = divide * tone.x;
        color.y = divide * tone.y;
        color.z = divide * tone.z;
    }
    else
    {
        color.x = gray * (1 - tone.x) + tone.x;
        color.y = gray * (1 - tone.y) + tone.y;
        color.z = gray * (1 - tone.z) + tone.z;
    }
}