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

/// \file       Identity.cpp
/// \date       02/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include <ThirdParty/Glm/glm/vec3.hpp>
#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Sepia.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Sepia::Sepia() : PostEffect(PostEffect::EType::Sepia, "Sepia")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("SepiaPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_thresholdID    = glGetUniformLocation(m_shaderID, "threshold");
    m_toneID         = glGetUniformLocation(m_shaderID, "tone");

    m_threshold = 0.25f;
    m_tone      = glm::vec4(0.3686, 0.1490, 0.0705, 1.0f);

    glUseProgram(m_shaderID);
    glUniform1f (m_thresholdID, m_threshold);
    glUniform3f (m_toneID, m_tone.x, m_tone.y, m_tone.z);
    glUseProgram(0);
}

/// \brief Destructor
Sepia::~Sepia() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void Sepia::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture,
                        uint shadowMapTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
}

/// \brief Called to draw the gui
void Sepia::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_Sepia", &m_bIsActive);

    ImGui::Text("\nThreshold");
    if(ImGui::SliderFloat("###Threshold_Sepia", &m_threshold, 0.0f, 1.0f, "Threshold = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_thresholdID, m_threshold);
        glUseProgram(0);
    }

    ImGui::Text("\nTone");
    if(ImGui::ColorEdit4("###Tone_Sepia", &m_tone[0]))
    {
        glUseProgram(m_shaderID);
        glUniform3f (m_toneID, m_tone.x, m_tone.y, m_tone.z);
        glUseProgram(0);
    }
}

} // !namespace