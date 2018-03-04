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

/// \file       GodRay.cpp
/// \date       04/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/GodRay.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
GodRay::GodRay() : PostEffect(PostEffect::EType::GodRay, "God ray")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("GodRayPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_depthTextureID = glGetUniformLocation(m_shaderID, "depthTexture");

    m_decayID       = glGetUniformLocation(m_shaderID, "decay");
    m_intensityID   = glGetUniformLocation(m_shaderID, "intensity");
    m_sampleCountID = glGetUniformLocation(m_shaderID, "sampleCount");

    m_decay       = 0.96875f;
    m_intensity   = 0.125f;
    m_sampleCount = 128;

    glUseProgram(m_shaderID);
    glUniform1f (m_decayID, m_decay);
    glUniform1f (m_intensityID, m_intensity);
    glUniform1i (m_sampleCountID, m_sampleCount);
    glUseProgram(0);
}

/// \brief Destructor
GodRay::~GodRay() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
void GodRay::ApplyEffect(uint colorTexture, uint depthTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture  (GL_TEXTURE_2D, depthTexture);
    glUniform1i    (m_depthTextureID, 1);
}

/// \brief Called to draw the GUI
void GodRay::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_GodRay", &m_bIsActive);

    ImGui::Text("\nIntensity");
    if(ImGui::SliderFloat("###Intensity_GodRay", &m_intensity, 0.0f, 0.4f, "Intensity = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_intensityID, m_intensity);
        glUseProgram(0);
    }

    ImGui::Text("\nDecay");
    if(ImGui::SliderFloat("###Decay_GodRay", &m_decay, 0.8, 1, "Decay = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_decayID, m_decay);
        glUseProgram(0);
    }

    ImGui::Text("\nSamples");
    if(ImGui::SliderInt("###Samples_GodRay", &m_sampleCount, 0, 500))
    {
        glUseProgram(m_shaderID);
        glUniform1i (m_sampleCountID, m_sampleCount);
        glUseProgram(0);
    }
}

} // !namespace