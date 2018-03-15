/// Copyright (C) 2018-2019, Cardinal Engine
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file       TextureImporter.cpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

#include <cstdio>
#include <cstring>
#include "Glew/include/GL/glew.h"
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Texture/TextureImporter.hpp"

/// \namespace cardinal
namespace cardinal
{

// TODO : Encapsulate image formats into wrapper
// TODO : Make a generic resource for textures

/// \brief  Imports a BMP file into the engine
/// \param  szPath The path to the file to import
/// \param  property The properties of the texture
/// \param  True on success, false on failure
/* static */ bool TextureImporter::ImportTexture_BMP(const char* szPath, TextureProperty & property)
{
    uchar header[54];
    uint  dataPos       = 0;
    uint  imageSize     = 0;
    uint  width, height = 0;
    property.alpha      = false;

    // TODO : Use engine platform wrapper
    FILE *file = fopen(szPath, "rb");
    if (!file)
    {
        Logger::LogError("Error while importing the texture %s, "
                         "could not be opened. Wrong directory ?", szPath);
        return false;
    }

    // Header processing
    if (fread(header, 1, 54, file) != 54)
    {
        Logger::LogError("Error while importing the texture %s, "
                         "wrong header format", szPath);
        fclose(file);
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        Logger::LogError("Error while importing the texture %s, "
                         "Not a BMP image", szPath);
        fclose(file);
        return false;
    }

    // Make sure this is a 24bpp file
    if (*(int *) &(header[0x1E]) != 0)
    {
        Logger::LogError("Error while importing the texture %s, "
                         "could not read the bpp", szPath);
        fclose(file);
        return false;
    }

    if (*(int *) &(header[0x1C]) != 24)
    {
        Logger::LogError("Error while importing the texture %s, "
                         "the texture is not 24 bpp", szPath);
        fclose(file);
        return false;
    }

    // Read the information about the image
    dataPos   = *(uint *) &(header[0x0A]);
    imageSize = *(uint *) &(header[0x22]);
    width     = *(uint *) &(header[0x12]);
    height    = *(uint *) &(header[0x16]);

    property.width  = width;
    property.height = height;

    if (imageSize == 0)
    {
        // RGB
        imageSize = width * height * 3;
    }

    if (dataPos == 0)
    {
        dataPos = 54;
    }

    // Gets texture data
    fread(property.pBuffer, 1, imageSize, file);
    fclose(file);

    Logger::LogInfo("Texture %s successfully imported", szPath);
    return true;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

/// \brief  Imports a BMP file into the engine
/// \param  szPath The path to the file to import
/// \param  property The properties of the texture
/// \param  True on success, false on failure
bool TextureImporter::ImportTexture_DDS(const char * szPath, TextureImporter::TextureProperty &property)
{
    property.alpha        = true;
    uchar header[124]     = {0};
    char fileCode[4]      = {0};
    unsigned int buffSize = 0;
    FILE * fp             = nullptr;

    fp = fopen(szPath, "rb");
    if (fp == nullptr)
    {
        Logger::LogError("Error while importing the texture %s, "
                         "could not be opened. Wrong directory ?", szPath);
        return false;
    }

    fread(fileCode, 1, 4, fp);
    if (strncmp(fileCode, "DDS ", 4) != 0)
    {
        Logger::LogError("Error while importing the texture %s, "
                         "not a dds file. Wrong directory ?", szPath);
        return false;
    }

    fread(&header, 124, 1, fp);
    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width	     = *(unsigned int*)&(header[12]);
    unsigned int linearSize	 = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    buffSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    fread(property.pBuffer, 1, buffSize, fp);
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            return false;
    }

    property.format      = format;
    property.width       = width;
    property.height      = height;
    property.mipmapCount = mipMapCount;
    property.blockSize   = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;

    return true;
}

} // !namespace