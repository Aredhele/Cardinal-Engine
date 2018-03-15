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

/// \file       Fog.cpp
/// \date       15/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Fog.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Fog::Fog() : PostEffect(PostEffect::EType::Fog, "Fog")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("FogPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_depthTextureID = glGetUniformLocation(m_shaderID, "depthTexture");

    m_fogColorID   = glGetUniformLocation(m_shaderID, "fogColor");
    m_fogDensityID = glGetUniformLocation(m_shaderID, "fogDensity");

    m_fogDensity = 2.0f;
    m_fogColor   = glm::vec3(0.7f, 0.7f, 0.7f);

    glUseProgram(m_shaderID);
    glUniform3f (m_fogColorID,   m_fogColor.x, m_fogColor.y, m_fogColor.z);
    glUniform1f (m_fogDensityID, m_fogDensity);
    glUseProgram(0);
}

/// \brief Destructor
Fog::~Fog() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void Fog::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture, uint shadowMapTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture  (GL_TEXTURE_2D, depthTexture);
    glUniform1i    (m_depthTextureID, 1);
}

/// \brief Called to display the GUI
void Fog::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_Fog", &m_bIsActive);

    ImGui::Text("\nFog distance");
    if(ImGui::ColorEdit3("###FogDistance", &m_fogColor[0]))
    {
        glUseProgram(m_shaderID);
        glUniform3f (m_fogColorID,   m_fogColor.x, m_fogColor.y, m_fogColor.z);
        glUseProgram(0);
    }

    ImGui::Text("\nFog density");
    if(ImGui::SliderFloat("###FogDensity", &m_fogDensity, 0.0f, 10.0f, "Fog density = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_fogDensityID, m_fogDensity);
        glUseProgram(0);
    }
}

} // !namespace