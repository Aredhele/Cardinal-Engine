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

/// \file       ShaderManager.hpp
/// \date       13/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_SHADER_MANAGER_HPP__
#define CARDINAL_ENGINE_SHADER_MANAGER_HPP__

#include <string>
#include <unordered_map>

#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class ShaderManager
/// \brief Stores shaders ID and provides a way to access it
class ShaderManager
{
public:

    // TODO : Encapsulate all static methods

    /// \brief Initializes the shader manager
    ///        Initializes the manager instance
    static void Initialize();

    /// \brief Destroys the shader manager
    ///        Destroys the manager instance
    static void Shutdown  ();

    /// \brief Registers a shader in the manager from a key and a value
    /// \param shaderKey The key of the shader
    /// \param shaderID The value
    static void Register(std::string const& shaderKey, int shaderID);

    /// \brief Unregisters a shader in the manager
    ///        Frees the shader in the video card memory
    /// \param shaderKey The shader to unregister
    static void Unregister(std::string const& shaderKey);

    /// \brief Returns the shader ID references by the given key
    /// \param shaderKey The key of the shader
    /// \return The shader ID
    static int GetShaderID(std::string const& shaderKey);

private:

    static ShaderManager * s_pInstance;

private:

    /// \brief  Default constuctor
    ShaderManager();

    // TODO : Use IDs
    // TODO : Destructor

    std::unordered_map<std::string, int> m_textureIDs;
};

} // !namespace

#endif // !CARDINAL_ENGINE_SHADER_MANAGER_HPP__