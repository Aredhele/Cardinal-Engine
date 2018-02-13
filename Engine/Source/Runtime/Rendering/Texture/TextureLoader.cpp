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

/// \file       TextureLoader.cpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Texture/TextureLoader.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ TextureLoader * TextureLoader::s_pInstance = nullptr;

/// \brief Default constructor
TextureLoader::TextureLoader()
: m_pDataBuffer(nullptr)
{
    // None
}

/// \brief Initializes the loader manager
///        Initializes the loader instance
void TextureLoader::Initialize()
{
    if(TextureLoader::s_pInstance == nullptr)
    {
        TextureLoader::s_pInstance = new TextureLoader();
        TextureLoader::s_pInstance->m_pDataBuffer = new uchar[1024 * 2024];

        ASSERT_NOT_NULL(TextureLoader::s_pInstance->m_pDataBuffer);
        Logger::LogInfo("Texture loader successfully initialized");
    }
    else
    {
        Logger::LogWaring("The texture loader is already initialized");
    }
}

/// \brief Destroys the loader manager
///        Destroys the loader instance
void TextureLoader::Shutdown()
{
    if(TextureLoader::s_pInstance != nullptr)
    {
        delete[] TextureLoader::s_pInstance->m_pDataBuffer;
        delete   TextureLoader::s_pInstance;

        TextureLoader::s_pInstance = nullptr;
        Logger::LogInfo("Texture loader successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The texture loader is already destroyed");
    }
}

/// \brief Loads a texture from a path and register it into the engine
void TextureLoader::LoadTexture(std::string const& path)
{
    // TODO
}

/// \brief Loads a bunch of textures from a list
void TextureLoader::LoadTextures(std::vector<std::string> const& paths)
{
    // TODO
}

} // !namespace
