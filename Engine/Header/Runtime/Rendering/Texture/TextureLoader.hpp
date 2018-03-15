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

/// \file       TextureLoader.hpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_TEXTURE_LOADER_HPP__
#define CARDINAL_ENGINE_TEXTURE_LOADER_HPP__

#include <string>
#include <vector>

#include "Runtime/Platform/Configuration/Configuration.hh"
#include "Runtime/Rendering/Texture/TextureImporter.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class  TextureLoader
/// \brief
class TextureLoader
{
private:

    static TextureLoader * s_pInstance; ///< The loader instance

public:

    // TODO : Encapsulate all static methods

    /// \brief Initializes the texture loader
    ///        Initializes the loader instance
    static void Initialize();

    /// \brief Destroys the texture loader
    ///        Destroys the loader instance
    static void Shutdown  ();

    /// \brief Loads a texture from a path and register it into the
    /// \param key The key of the texture
    /// \param path The path of the texture
    static void LoadTexture(std::string const& key, std::string const& path, bool nearest = false);

    /// \brief Loads a bunch of textures from a list
    /// \param keys Texture keys
    /// \param paths Texture paths
    static void LoadTextures(std::vector<std::string> const& keys,
                             std::vector<std::string> const& paths);

    /// \brief Generates mip mapping from textures
    /// \param key The key of the texture
    /// \param path The path of the textures
    static void LoadMipMapTextures(std::string const& key,
                                   std::vector<std::string> paths);

private:

    /// \brief Binds the texture and load into OpenGL
    /// \param property Properties of the texture
    /// \return The ID of the texture
    static uint BindTexture(TextureImporter::TextureProperty const& property, bool nearest = false);

    /// \brief Binds the texture and load into OpenGL
    /// \param prop The vector of properties
    /// \return The ID of the texture
    static uint BindTexture(std::vector<TextureImporter::TextureProperty> const& prop);

private:

    /// \brief Default constructor
    TextureLoader();

    // TODO : Uses the main engine stack allocator
    uchar * m_pDataBuffer;
};

} // !namespace

#endif // !CARDINAL_ENGINE_TEXTURE_LOADER_HPP__