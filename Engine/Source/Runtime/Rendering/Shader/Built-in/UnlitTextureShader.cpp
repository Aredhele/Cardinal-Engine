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

/// \file       UnlitColorShader.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader/Built-in
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/UnlitTextureShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
UnlitTextureShader::UnlitTextureShader()
{
    m_shaderID = ShaderManager::GetShaderID("UnlitTexture");
    m_matrixID = glGetUniformLocation(m_shaderID, "MVP");
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void UnlitTextureShader::Begin(const glm::mat4 &MVP)
{
    glUseProgram      (m_shaderID);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    // TODO : Bind texture
}

/// \brief Restore the pipeline state
void UnlitTextureShader::End()
{
    // None
}

} // !namespace



