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

/// \file       Bloom.cpp
/// \date       05/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Bloom.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Bloom::Bloom() : PostEffect(PostEffect::EType::Bloom, "Bloom")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("BloomPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_colorID        = glGetUniformLocation(m_shaderID, "bloomColor");
    m_qualityID      = glGetUniformLocation(m_shaderID, "quality"),
    m_sampleCountID  = glGetUniformLocation(m_shaderID, "sampleCount");

    m_color       = glm::vec3(0.8f);
    m_quality     = 2.5f;
    m_sampleCount = 5;

    glUseProgram(m_shaderID);
    glUniform1f (m_qualityID, m_quality);
    glUniform1i (m_sampleCountID, m_sampleCount);
    glUniform3f (m_colorID, m_color.x, m_color.y, m_color.z);
    glUseProgram(0);
}

/// \brief Destructor
Bloom::~Bloom() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void Bloom::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
}

/// \brief Called to draw the GUI
void Bloom::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_Bloom", &m_bIsActive);

    ImGui::Text("\nQuality");
    if(ImGui::SliderFloat("###Quality_Bloom", &m_quality, 0.0f, 10.0f, "Quality = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_qualityID, m_quality);
        glUseProgram(0);
    }

    ImGui::Text("\nTone");
    if(ImGui::ColorEdit4("###Tone_Bloom", &m_color[0]))
    {
        glUseProgram(m_shaderID);
        glUniform3f (m_colorID, m_color.x, m_color.y, m_color.z);
        glUseProgram(0);
    }

    ImGui::Text("\nSamples");
    if(ImGui::SliderInt("###Sample_Bloom", &m_sampleCount, 0, 100, "Samples = %d"))
    {
        glUseProgram(m_shaderID);
        glUniform1i (m_sampleCountID, m_sampleCount);
        glUseProgram(0);
    }
}

} // !namespace