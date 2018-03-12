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

/// \file       UnlitLineShader.cpp
/// \date       13/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader/Built-in
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Unlit/UnlitLineShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
UnlitLineShader::UnlitLineShader()
{
    m_shaderID = ShaderManager::GetShaderID("LineShader");
    m_matrixID = glGetUniformLocation((uint)m_shaderID, "MVP");
    m_colorID  = glGetUniformLocation((uint)m_shaderID, "lineColor");
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void UnlitLineShader::Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    glUseProgram      ((uint)m_shaderID);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform3f       (m_colorID,  m_color.x, m_color.y, m_color.z);
}

/// \brief Restore the pipeline state
void UnlitLineShader::End()
{
    // None
}

/// \brief Sets the color of the line
void UnlitLineShader::SetColor(glm::vec3 const& color)
{
    m_color = color;
}

} // !namespace



