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

/// \file       Vignette.cpp
/// \date       05/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Vignette.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Vignette::Vignette() : PostEffect(PostEffect::EType::Vignette, "Vignette")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("VignettePostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_radiusID       = glGetUniformLocation(m_shaderID, "radius");
    m_softnessID     = glGetUniformLocation(m_shaderID, "softness");
    m_centerID       = glGetUniformLocation(m_shaderID, "center");
    m_opacityID      = glGetUniformLocation(m_shaderID, "opacity");

    m_radius   = 0.25f;
    m_softness = 0.45f;
    m_center   = glm::vec2(0.5f, 0.5f);
    m_opacity  = 0.5f;

    glUseProgram(m_shaderID);
    glUniform1f (m_radiusID,   m_radius);
    glUniform1f (m_softnessID, m_softness);
    glUniform1f (m_opacityID,  m_opacity);
    glUniform2f (m_centerID, m_center.x, m_center.y);
    glUseProgram(0);
}

/// \brief Destructor
Vignette::~Vignette() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void Vignette::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
}

/// \brief Called to draw the GUI
void Vignette::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_Vignette", &m_bIsActive);

    ImGui::Text("\nRadius");
    if(ImGui::SliderFloat("###Radius_Vignette", &m_radius, 0.0f, 1.0f, "Radius = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_radiusID,   1 - m_radius);
        glUseProgram(0);
    }

    ImGui::Text("\nSoftness");
    if(ImGui::SliderFloat("###Softness_Vignette", &m_softness, 0.0f, 1.0f, "Softness = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_softnessID,   m_softness);
        glUseProgram(0);
    }

    ImGui::Text("\nOpacity");
    if(ImGui::SliderFloat("###Opacity_Vignette", &m_opacity, 0.0f, 1.0f, "Opacity = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_opacityID,   m_opacity);
        glUseProgram(0);
    }

    ImGui::Text("\nCenter");
    if(ImGui::InputFloat2("###Center_Vignette", &m_center[0], 3))
    {
        glUseProgram(m_shaderID);
        glUniform2f (m_centerID, m_center.x, m_center.y);
        glUseProgram(0);
    }
}

} // !namespace