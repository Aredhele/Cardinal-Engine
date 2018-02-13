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

/// \file       TextureManager.hpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_TEXTURE_MANAGER_HPP__
#define CARDINAL_ENGINE_TEXTURE_MANAGER_HPP__

#include <string>
#include <unordered_map>

#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class TextureManager
/// \brief Stores textures ID and provides a way to access it
class TextureManager
{
public:

    // TODO : Encapsulate all static methods

    /// \brief Initializes the texture manager
    ///        Initializes the manager instance
    static void Initialize();

    /// \brief Destroys the texture manager
    ///        Destroys the manager instance
    static void Shutdown  ();

    /// \brief Registers a texture in the manager from a key and a value
    /// \param textureKey The key of the texture
    /// \param textureID The value
    static void Register(std::string const& textureKey, uint textureID);

    /// \brief Unregisters a texture in the manager
    ///        Frees the texture in the video card memory
    /// \param textureKey The texture to unregister
    static void Unregister(std::string const& textureKey);

    /// \brief Returns the texture ID references by the given key
    /// \param textureKey The key of the texture
    /// \return The texture ID
    static uint GetTextureID(std::string const& textureKey);

private:

    static TextureManager * s_pInstance;

private:

    /// \brief  Default constuctor
    TextureManager();

    // TODO : Use IDs
    // TODO : Destructor

    std::unordered_map<std::string, uint> m_textureIDs;
};

} // !namespace

#endif // !CARDINAL_ENGINE_TEXTURE_MANAGER_HPP__