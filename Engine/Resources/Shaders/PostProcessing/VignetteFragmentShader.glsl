#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform float     radius;
uniform float     softness;
uniform vec2      center;
uniform float     opacity;

void main(void)
{
   	vec3 texColor = texture(colorTexture, textureUV).rgb;
   	vec2 position = textureUV - center;
   	float len = length(position);
   	float vignette = smoothstep(radius, radius - softness, len);
   	color = mix(texColor, texColor * vignette, opacity).rgb;
}