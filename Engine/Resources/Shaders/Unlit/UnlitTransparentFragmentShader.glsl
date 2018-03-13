#version 330 core

// In
in vec2 UV;

// Out
out vec3 color;

// Uniforms
uniform sampler2D colorTexture;

void main()
{
    // Samples the texture to check the transparency
    vec3 rgb = texture(colorTexture, UV).rgb;

    // If the pixel is fully white, the fragment is transparent
    if(rgb.x == 1.0f && rgb.y == 1.0f && rgb.z == 1.0f)
    {
        // Drops the fragment
        discard;
    }

    // Otherwise it's a regular color
    color = rgb;
}