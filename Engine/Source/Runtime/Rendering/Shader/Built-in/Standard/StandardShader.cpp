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
#include "Runtime/Rendering/Shader/Built-in/Standard/StandardShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ int StandardShader::s_lightDirection   = -1;
/* static */ int StandardShader::s_lightIntensity   = -1;
/* static */ int StandardShader::s_ambientIntensity = -1;
/* static */ int StandardShader::s_lightColor       = -1;

/// \brief Constructor
StandardShader::StandardShader()
{
    m_viewID         = -1;
    m_modelID        = -1;
    m_textureID      =  0;
    m_textureSampler = -1;
    m_lightCountID   = -1;

    m_shaderID       = ShaderManager::GetShaderID("Standard");

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

    /*ASSERT_NE(m_modelID,  -1);
    ASSERT_NE(m_viewID,   -1);
    ASSERT_NE(m_matrixID, -1);
    ASSERT_NE(s_lightPosition,    -1);
    ASSERT_NE(s_lightIntensity,   -1);
    ASSERT_NE(s_ambientIntensity, -1);
    ASSERT_NE(s_lightColor,       -1);*/

    // Lighting
    m_lightCountID = glGetUniformLocation((GLuint)m_shaderID, "lightCount");

   // ASSERT_NE(m_lightCountID, -1);
}

/// \brief Sets the texture of the shader
void StandardShader::SetTexture(uint textureID)
{
    m_textureID = textureID;
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void StandardShader::Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    glUseProgram      ((GLuint)m_shaderID);
    glUniformMatrix4fv(m_projection,  1, GL_FALSE,   &P[0][0]);
    glUniformMatrix4fv(m_modelID,     1, GL_FALSE,   &M[0][0]);
    glUniformMatrix4fv(m_viewID,      1, GL_FALSE,   &V[0][0]);
    glUniformMatrix4fv(m_matrixID,    1, GL_FALSE, &MVP[0][0]);

    // Lighting
    glUniform1i(m_lightCountID, static_cast<GLint>(pointLights.size()));

    // Setting uniforms
    for(size_t nLight = 0; nLight < pointLights.size(); ++nLight)
    {
        std::string index = std::to_string(nLight);
        std::string range      = "lights[" + index + "].range";
        std::string intensity  = "lights[" + index + "].intensity";
        std::string color      = "lights[" + index + "].color";
        std::string position   = "lights[" + index + "].position";

        int locRange     = glGetUniformLocation((GLuint)m_shaderID, range.c_str());
        int locIntensity = glGetUniformLocation((GLuint)m_shaderID, intensity.c_str());
        int locColor     = glGetUniformLocation((GLuint)m_shaderID, color.c_str());
        int locPosition  = glGetUniformLocation((GLuint)m_shaderID, position.c_str());

        glUniform1f(locRange,     pointLights[nLight].range);
        glUniform1f(locIntensity, pointLights[nLight].intensity);
        glUniform3f(locColor,     pointLights[nLight].color.x,    pointLights[nLight].color.y,    pointLights[nLight].color.z);
        glUniform3f(locPosition,  pointLights[nLight].position.x, pointLights[nLight].position.y, pointLights[nLight].position.z);
    }

    glActiveTexture (GL_TEXTURE0);
    glBindTexture   (GL_TEXTURE_2D, m_textureID);
}

/// \brief Restore the pipeline state
void StandardShader::End()
{
    // None
}

} // !namespace



