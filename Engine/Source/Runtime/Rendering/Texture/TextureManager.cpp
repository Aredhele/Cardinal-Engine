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

/// \file       TextureManager.cpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

/// \namespace cardinal
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Texture/TextureManager.hpp"

namespace cardinal
{

/* static */ TextureManager * TextureManager::s_pInstance = nullptr;

/// \brief Initializes the texture manager
///        Initializes the manager instance
/* static */ void cardinal::TextureManager::Initialize()
{
    if(TextureManager::s_pInstance == nullptr)
    {
        TextureManager::s_pInstance = new TextureManager();
        Logger::LogInfo("Texture manager successfully initialized");
    }
    else
    {
        Logger::LogWaring("The texture manager is already initialized");
    }
}

/// \brief Destroys the texture manager
///        Destroys the manager instance
/* static */ void cardinal::TextureManager::Shutdown()
{
    if(TextureManager::s_pInstance != nullptr)
    {
        delete TextureManager::s_pInstance;
        TextureManager::s_pInstance = nullptr;

        Logger::LogInfo("Texture manager successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The texture manager is already destroyed");
    }
}

/// \brief Registers a texture in the manager from a key and a value
/// \param textureKey The key of the texture
/// \param textureID The value
/* static */ void cardinal::TextureManager::Register(std::string const& textureKey, uint textureID)
{
    ASSERT_NE      (textureID, 0);
    ASSERT_NE      (textureKey, "");
    ASSERT_NOT_NULL(TextureManager::s_pInstance);

    TextureManager::s_pInstance->m_textureIDs.emplace(textureKey, textureID);
}

/// \brief Unregisters a texture in the manager
///        Frees the texture in the video card memory
/// \param textureKey The texture to unregister
/* static */ void cardinal::TextureManager::Unregister(std::string const& textureKey)
{
    ASSERT_NE      (textureKey, "");
    ASSERT_NOT_NULL(TextureManager::s_pInstance);

    auto it = TextureManager::s_pInstance->m_textureIDs.find(textureKey);
    if(it != TextureManager::s_pInstance->m_textureIDs.end())
    {
        TextureManager::s_pInstance->m_textureIDs.erase(it);
    }
}

/// \brief Returns the texture ID references by the given key
/// \param textureKey The key of the texture
/// \return The texture ID
/* static */ uint cardinal::TextureManager::GetTextureID(std::string const& textureKey)
{
    uint id = 0;
    auto it = TextureManager::s_pInstance->m_textureIDs.find(textureKey);

    if(it != TextureManager::s_pInstance->m_textureIDs.end())
    {
       id = it->second;
    }

    return id;
}

} // !namespace