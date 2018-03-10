#version 330 core

// In
layout(location = 0) in vec3 vertexCoord;
layout(location = 1) in vec4 position;
layout(location = 2) in vec3 color;

// Out
out vec3 particleColor;

// Uniforms
uniform vec3 cameraRightWorld;
uniform vec3 cameraUpWorld;
uniform mat4 VP;

void main()
{
	float particleSize    = position.w;
	vec3 centerWorldSpace = position.xyz;

	vec3 vertexPositionWorld = centerWorldSpace
		+ cameraRightWorld * vertexCoord.x * particleSize
		+ cameraUpWorld    * vertexCoord.y * particleSize;

	// MVP -
	gl_Position   = VP * vec4(vertexPositionWorld, 1.0f);
	particleColor = color;
}