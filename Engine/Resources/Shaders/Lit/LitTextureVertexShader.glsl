#version 330 core

// In
layout(location = 0) in vec3 vertexPositionModel;
layout(location = 1) in vec3 vertexNormalModel;
layout(location = 2) in vec2 vertexUV;

// Out
out vec2 UV;
out vec3 vertexNormalView;
out vec3 lightDirectionView;
out vec3 cameraDirectionView;
out vec3 vertexPositionWorld;

// Uniforms
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPositionWorld;

void main()
{
    gl_Position         =  MVP * vec4(vertexPositionModel, 1.0f);
    vertexPositionWorld = (M   * vec4(vertexPositionModel, 1.0f)).xyz;

    vec3 vertexPositionView = (V * M * vec4(vertexPositionModel,1)).xyz;
    cameraDirectionView     = vec3(0.0f, 0.0f, 0.0f) - vertexPositionView;

    vec3 lightPositionView  = (V * vec4(LightPositionWorld, 1.0f)).xyz;
    lightDirectionView      = lightPositionView + cameraDirectionView;

    vertexNormalView = (V * M * vec4(vertexNormalModel, 0.0f)).xyz;
    UV               = vertexUV;
}