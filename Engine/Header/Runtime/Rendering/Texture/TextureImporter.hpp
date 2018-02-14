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

/// \file       TextureImporter.hpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_TEXTURE_IMPORTER_HPP__
#define CARDINAL_ENGINE_TEXTURE_IMPORTER_HPP__

#include "Runtime/Platform/Configuration/Type.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class TextureImporter
/// \brief Textures importer
class TextureImporter
{
public :

    /// \brief Stores informations about a texture
    struct TextureProperty
    {
        uchar * pBuffer; ///< The data of the texture
        uint    width;   ///< The width of the texture
        uint    height;  ///< The height of the texture
    };

    /// \brief  Imports a BMP file into the engine
    /// \param  szPath The path to the file to import
    /// \param  property The properties of the texture
    /// \param  True on success, false on failure
    static bool ImportTexture_BMP(const char* szPath, TextureProperty & property);
};

} // !namespace

#endif // !CARDINAL_ENGINE_TEXTURE_IMPORTER_HPP__