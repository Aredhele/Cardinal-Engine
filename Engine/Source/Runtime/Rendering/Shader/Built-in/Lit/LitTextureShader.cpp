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

/// \file       LitTextureShader.cpp
/// \date       20/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader/Built-in/Lit
/// \author     Vincent STEHLY--CALISTO

#include <Header/Runtime/Core/Assertion/Assert.hh>
#include <ThirdParty/Glm/glm/ext.hpp>
#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Lit/LitTextureShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ int LitTextureShader::s_lightDirection   = -1;
/* static */ int LitTextureShader::s_lightIntensity   = -1;
/* static */ int LitTextureShader::s_ambientIntensity = -1;
/* static */ int LitTextureShader::s_lightColor       = -1;

/// \brief Constructor
LitTextureShader::LitTextureShader()
{
    m_viewID         = -1;
    m_modelID        = -1;
    m_textureID      =  0;
    m_textureSampler = -1;

    m_shaderID       = ShaderManager::GetShaderID("LitTexture");

    ASSERT_NE(m_shaderID, -1);

    m_projection     = glGetUniformLocation((GLuint)m_shaderID, "PR");
    m_modelID        = glGetUniformLocation((GLuint)m_shaderID, "M");
    m_viewID         = glGetUniformLocation((GLuint)m_shaderID, "V");
    m_matrixID       = glGetUniformLocation((GLuint)m_shaderID, "MVP");
    m_textureSampler = glGetUniformLocation((GLuint)m_shaderID, "textureSampler");

    s_lightDirection   = glGetUniformLocation((GLuint)m_shaderID, "lightDirection");
    s_lightIntensity   = glGetUniformLocation((GLuint)m_shaderID, "lightIntensity");
    s_ambientIntensity = glGetUniformLocation((GLuint)m_shaderID, "ambientIntensity");
    s_lightColor       = glGetUniformLocation((GLuint)m_shaderID, "lightColor");

   /* ASSERT_NE(m_modelID,  -1);
    ASSERT_NE(m_viewID,   -1);
    ASSERT_NE(m_matrixID, -1);
    ASSERT_NE(s_lightDirection,   -1);
    ASSERT_NE(s_lightIntensity,   -1);
    ASSERT_NE(s_ambientIntensity, -1);
    ASSERT_NE(s_lightColor,       -1);*/
}

/// \brief Sets the texture of the shader
void LitTextureShader::SetTexture(uint textureID)
{
    m_textureID = textureID;
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void LitTextureShader::Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    glUseProgram      ((GLuint)m_shaderID);
    glUniformMatrix4fv(m_projection,  1, GL_FALSE,   &P[0][0]);
    glUniformMatrix4fv(m_modelID,     1, GL_FALSE,   &M[0][0]);
    glUniformMatrix4fv(m_viewID,      1, GL_FALSE,   &V[0][0]);
    glUniformMatrix4fv(m_matrixID,    1, GL_FALSE, &MVP[0][0]);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture   (GL_TEXTURE_2D, m_textureID);
}

/// \brief Restore the pipeline state
void LitTextureShader::End()
{
    // None
}

} // !namespace



