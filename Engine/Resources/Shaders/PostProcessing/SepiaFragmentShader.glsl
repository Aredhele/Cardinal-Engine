#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;

void main(void)
{
    // Sepia tone
    vec3 sepia = vec3(0.3686, 0.1490, 0.0705);

    // Threshold
    float threshold = 0.25f;

    // Fragment gray scale
    vec3 _color = texture2D(colorTexture, textureUV).rgb;
    float gray = dot(_color, vec3(0.299, 0.587, 0.114));

    if(gray < threshold)
    {
        float divide = gray / threshold;
        color.x = divide * sepia.x;
        color.y = divide * sepia.y;
        color.z = divide * sepia.z;
    }
    else
    {
        color.x = gray * (1 - sepia.x) + sepia.x;
        color.y = gray * (1 - sepia.y) + sepia.y;
        color.z = gray * (1 - sepia.z) + sepia.z;
    }
}