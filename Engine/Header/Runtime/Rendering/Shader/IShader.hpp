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

/// \file       Shader.hpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_I_SHADER_HPP__
#define CARDINAL_ENGINE_I_SHADER_HPP__

#include "Glm/glm/glm.hpp"
#include "Runtime/Platform/Configuration/Type.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class IShader
/// \brief Base class for all built-in shaders
class IShader
{
public:

    /// \brief Sets up the pipeline for the shader
    /// \param MVP The Projection-View-Model matrix to pass to the shader
    /// \param TODO
    virtual void Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light) = 0;

    /// \brief Restore the pipeline state
    virtual void End  () = 0;

    /// \brief Sets 4 floats in the shader
    void SetFloat4(int uniform, float x, float y, float z, float w);

public:

     int m_shaderID = 0; ///< The shader to use
     int m_matrixID = 0; ///< The MVP matrix ID
};

} // !namespace 

#endif // !CARDINAL_ENGINE_I_SHADER_HPP__