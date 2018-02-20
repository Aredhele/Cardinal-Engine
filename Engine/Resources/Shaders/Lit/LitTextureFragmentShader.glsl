#version 330 core

// In
in vec2 UV;
in vec3 vertexNormalView;
in vec3 lightDirectionView;
in vec3 cameraDirectionView;
in vec3 vertexPositionWorld;

// Ouput data
out vec3 color;

// Uniforms
uniform sampler2D textureSampler;
uniform vec3      LightPositionWorld;
uniform mat4      MV;

void main()
{
	vec3  LightColor = vec3(1.0f, 1.0f, 1.0f); // TODO
	float LightPower = 50.0f;

	// Material properties
	vec3 MaterialDiffuseColor  = texture(textureSampler, UV).rgb;
	vec3 MaterialAmbientColor  = vec3(0.1f, 0.1f, 0.1f) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3f, 0.3f, 0.3f);

	// Distance to the light
	float distance = length(LightPositionWorld - vertexPositionWorld);

	// Normal of the computed fragment, in camera space
	vec3 n = normalize(vertexNormalView);

	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(lightDirectionView);

	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(n, l), 0, 1);

	// Eye vector (towards the camera)
	vec3 E = normalize(cameraDirectionView);

	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);

	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(E, R), 0, 1);

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);

}