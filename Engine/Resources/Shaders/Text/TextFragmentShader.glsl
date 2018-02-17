#version 330 core

// In
in vec2 UV;

// Out
out vec4 color;

// Uniforms
uniform vec4      textColor;
uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, UV);

	if(color.x == 0.0f && color.y == 0.0f && color.z == 0.0f)
	{
	    discard;
	}

	color = textColor;
}