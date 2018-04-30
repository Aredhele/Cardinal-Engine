#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;
uniform sampler2D whiteNoiseTexture;
uniform float time;
uniform float intensity;

float rand(float n){return fract(sin(n) * 43758.5453123);}

float rand(vec2 n) {
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

void main(void)
{
  vec2 shift = vec2(0.0f, 0.0f);
  vec3 colorShift = vec3(0.0f, 0.0f, 0.0f);

  if(rand(time) > 1.5 - intensity)
  {
     shift = vec2(0.5f, 0.2f);
  }

  if(rand(cos(time)) > 1.5 - intensity)
  {
      colorShift.g = rand(cos(time));
      colorShift.r = rand(cos(time) + 2);
      colorShift.b = rand(cos(time) + 18);
  }

  if(rand(textureUV)  > 1 - intensity)
    color = texture(colorTexture, textureUV + shift + rand(textureUV * sin(time))).rgb;
  else
    color = texture(colorTexture, textureUV + shift).rgb;

    color += colorShift;
}
