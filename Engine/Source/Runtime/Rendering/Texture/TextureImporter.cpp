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
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Texture/TextureImporter.hpp"

/// \namespace cardinal
namespace cardinal
{

// TODO : Encapsulate image formats into wrapper
// TODO : Make a generic resource for textures

/// \brief  Imports a BMP file into the engine
/// \param  szPath The path to the file to import
/// \param  pBuffer The buffer to store texture data
/* static */ bool TextureImporter::ImportTexture_BMP(const char* szPath, uchar * pBuffer)
{
    uchar header[54];
    uint  dataPos       = 0;
    uint  imageSize     = 0;
    uint  width, height = 0;

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
    fread(pBuffer, 1, imageSize, file);
    fclose(file);

    Logger::LogInfo("Texture %s successfully imported", szPath);
    return true;
}

} // !namespace