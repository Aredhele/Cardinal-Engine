#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;


/// Mirror X
void mirror_x()
{
    vec2 coord = textureUV;
    if (coord.x > 0.5)
    color = texture(colorTexture, vec2(1-coord.x, coord.y)).rgb;
    else
    color = texture(colorTexture, coord).rgb;
}

/// Mirror Y
void mirror_y()
{
    vec2 coord = textureUV;
    if (coord.y > 0.5)
    color = texture(colorTexture, vec2(coord.x, 1 - coord.y)).rgb;
    else
    color = texture(colorTexture, coord).rgb;
}

/// Grey
void grey()
{
    vec3 pColor = texture(colorTexture, textureUV).rgb;
    float lum = 0.2126 * pColor.r + 0.7152 * pColor.g + 0.0722 * pColor.b;
    color = vec3(lum, lum, lum);
}

/// Tint
void tint()
{
    vec3 tint = vec3(0.01568,0.5451,0.6039); // Tint definition (here Duck blue)
    vec3 pColor = texture(colorTexture, textureUV).rgb;
    float lum = 0.2126 * pColor.r + 0.7152 * pColor.g + 0.0722 * pColor.b;
    color = lum * tint;
}

/// Guassian Blur
void blur()
{
    float transformation;
    float sum = 0;
    vec2 offset = vec2(1.0f / 1600.0f, 1.0f / 900.0f);
    int intensity = 2;

    int radius = 5;
    int half_radius = int(radius * 0.5f);
    float M[25];

    // Fill matrix and calcul total gaussian transformation
    for(int y = 0; y < radius; ++y)
    {
        for(int x = 0; x < radius; ++x)
        {
            float yc = y - half_radius;
            float xc = x - half_radius;
            transformation = exp( -(yc * yc + xc * xc) / (2 * intensity * intensity) );
            sum += transformation;
            M[y * radius + x] = transformation;
        }
    }

    // Process average in matrix
    for(int y = 0; y < radius ; y++)
    {
        for(int x = 0; x < radius; x++)
        {
            M[y * radius + x] /= sum;
        }
    }

    // Process final color
    for(int y = 0; y < radius; ++y)
    {
        for(int x = 0; x < radius; ++x)
        {
            float oX = (x - 2) * offset.x;
            float oY = (y - 2) * offset.y;
            color += (texture(colorTexture, vec2(textureUV.x + oX, textureUV.y + oY)).rgb) * M[y * radius + x];
        }
    }
}

/// Eye contour
void vignette()
{
    float pi = 3.1415;
    float hpi = pi * 0.5f;
    float luminance = (cos(textureUV.x * pi - hpi) + sin(textureUV.y * pi)) * 0.5f;

    color = texture(colorTexture, textureUV).rgb * luminance;
}

/// Negative
void negative()
{
    color = texture(colorTexture, textureUV).rgb;
    color.r = 1.f - color.r;
    color.g = 1.f - color.g;
    color.b = 1.f - color.b;
}

/// Protanopia colorblind simulation
void protanopia()
{
    // RGB to LMS matrix conversion
    vec3 input = texture(colorTexture, textureUV).rgb;
	float L = (17.8824f * input.x)   + (43.5161f * input.y)  + (4.11935f * input.z); //b ?
	float M = (3.45565f * input.x)   + (27.1554f * input.y)  + (3.86714f * input.z);
	float S = (0.0299566f * input.x) + (0.184309f * input.y) + (1.46709f * input.z);

    float l = 0.0f * L + 2.02344f * M + -2.52581f * S;
	float m = 0.0f * L + 1.0f * M + 0.0f * S;
	float s = 0.0f * L + 0.0f * M + 1.0f * S;

    // LMS to RGB matrix conversion
	color.x = (0.0809444479f * l) + (-0.130504409f * m) + (0.116721066f * s);
	color.y = (-0.0102485335f * l) + (0.0540193266f * m) + (-0.113614708f * s);
	color.z = (-0.000365296938f * l) + (-0.00412161469f * m) + (0.693511405f * s);
}

/// Protanopia colorblind simulation
void deuteronopia()
{
    // RGB to LMS matrix conversion
    vec3 input = texture(colorTexture, textureUV).rgb;
	float L = (17.8824f * input.x)   + (43.5161f * input.y)  + (4.11935f * input.z); //b ?
	float M = (3.45565f * input.x)   + (27.1554f * input.y)  + (3.86714f * input.z);
	float S = (0.0299566f * input.x) + (0.184309f * input.y) + (1.46709f * input.z);
    
	float l = 1.0f * L + 0.0f * M + 0.0f * S;
	float m = 0.494207f * L + 0.0f * M + 1.24827f * S;
	float s = 0.0f * L + 0.0f * M + 1.0f * S;

    // LMS to RGB matrix conversion
	color.x = (0.0809444479f * l) + (-0.130504409f * m) + (0.116721066f * s);
	color.y = (-0.0102485335f * l) + (0.0540193266f * m) + (-0.113614708f * s);
	color.z = (-0.000365296938f * l) + (-0.00412161469f * m) + (0.693511405f * s);
}

/// Protanopia colorblind simulation
void tritanopia()
{
    // RGB to LMS matrix conversion
    vec3 input = texture(colorTexture, textureUV).rgb;
	float L = (17.8824f * input.x)   + (43.5161f * input.y)  + (4.11935f * input.z); //b ?
	float M = (3.45565f * input.x)   + (27.1554f * input.y)  + (3.86714f * input.z);
	float S = (0.0299566f * input.x) + (0.184309f * input.y) + (1.46709f * input.z);
    
	float l = 1.0f * L + 0.0f * M + 0.0f * S;
	float m = 0.0f * L + 1.0f * M + 0.0f * S;
	float s = -0.395913f * L + 0.801109f * M + 0.0f * S;

    // LMS to RGB matrix conversion
	color.x = (0.0809444479f * l) + (-0.130504409f * m) + (0.116721066f * s);
	color.y = (-0.0102485335f * l) + (0.0540193266f * m) + (-0.113614708f * s);
	color.z = (-0.000365296938f * l) + (-0.00412161469f * m) + (0.693511405f * s);
}

void light_selection()
{
    vec3 pColor = texture(colorTexture, textureUV).rgb;
    float lum = 0.2126 * pColor.r + 0.7152 * pColor.g + 0.0722 * pColor.b;
    if (lum > 0.5)
        color = vec3(lum, lum, lum);
    else
        color = vec3(0,0,0);
}

void main(void)
{
    // mirror_x();
    // mirror_y();
    // grey();
    // tint();
    // blur();
    // vignette();
    // negative();
    // protanopia();
    // deuteronopia();
    // tritanopia();
    // light_selection();

    // no op
    color = texture(colorTexture, textureUV).rgb;
}