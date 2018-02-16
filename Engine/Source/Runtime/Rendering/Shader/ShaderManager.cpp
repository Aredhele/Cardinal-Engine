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

/// \file       ShadeManager.cpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ ShaderManager * ShaderManager::s_pInstance = nullptr;

/// \brief Default constructor
ShaderManager::ShaderManager()
{
    // None
}

/// \brief Initializes the shader manager
///        Initializes the manager instance
/* static */ void cardinal::ShaderManager::Initialize()
{
    if(ShaderManager::s_pInstance == nullptr)
    {
        ShaderManager::s_pInstance = new ShaderManager();
        Logger::LogInfo("IShader manager successfully initialized");
    }
    else
    {
        Logger::LogWaring("The shader manager is already initialized");
    }
}

/// \brief Destroys the shader manager
///        Destroys the manager instance
/* static */ void cardinal::ShaderManager::Shutdown()
{
    if(ShaderManager::s_pInstance != nullptr)
    {
        delete ShaderManager::s_pInstance;
        ShaderManager::s_pInstance = nullptr;

        Logger::LogInfo("IShader manager successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The shader manager is already destroyed");
    }
}

/// \brief Registers a shader in the manager from a key and a value
/// \param shaderKey The key of the shader
/// \param shaderID The value
/* static */ void cardinal::ShaderManager::Register(std::string const& shaderKey, uint shaderID)
{
    ASSERT_NE      (shaderID, 0);
    ASSERT_NE      (shaderKey, "");
    ASSERT_NOT_NULL(ShaderManager::s_pInstance);

    ShaderManager::s_pInstance->m_textureIDs.emplace(shaderKey, shaderID);
}

/// \brief Unregisters a shader in the manager
///        Frees the shader in the video card memory
/// \param shaderKey The shader to unregister
/* static */ void cardinal::ShaderManager::Unregister(std::string const& shaderKey)
{
    ASSERT_NE      (shaderKey, "");
    ASSERT_NOT_NULL(ShaderManager::s_pInstance);

    auto it = ShaderManager::s_pInstance->m_textureIDs.find(shaderKey);
    if(it != ShaderManager::s_pInstance->m_textureIDs.end())
    {
        ShaderManager::s_pInstance->m_textureIDs.erase(it);
    }
}

/// \brief Returns the shader ID references by the given key
/// \param shaderKey The key of the shader
/// \return The shader ID
/* static */ uint cardinal::ShaderManager::GetShaderID(std::string const& shaderKey)
{
    uint id = 0;
    auto it = ShaderManager::s_pInstance->m_textureIDs.find(shaderKey);

    if(it != ShaderManager::s_pInstance->m_textureIDs.end())
    {
        id = it->second;
    }

    return id;
}

} // !namespace