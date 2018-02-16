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

#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Shader/Built-in/UnlitColorShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void UnlitColorShader::Begin(const glm::mat4 &MVP)
{
    // Pre-condition
    ASSERT_NE(m_shaderID, 0);
    ASSERT_NE(m_matrixID, 0);

    glUseProgram      (m_shaderID);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);
}

/// \brief Restore the pipeline state
void UnlitColorShader::End()
{
    // None
}

} // !namespace



