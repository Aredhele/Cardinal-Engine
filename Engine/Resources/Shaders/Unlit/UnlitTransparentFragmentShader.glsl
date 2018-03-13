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
    vec2 correctUV = vec2(UV.x, 1.0 - UV.y);
    vec4 rgba       = texture(colorTexture, correctUV);

    // If the pixel is fully white, the fragment is transparent
    if(rgba.a != 1.0f)
    {
        // Drops the fragment
        discard;
    }

    // Otherwise it's a regular color
    color = rgba.rgb;
}