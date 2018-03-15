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

/// \file       DepthOfField.cpp
/// \date       14/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/DepthOfField.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
DepthOfField::DepthOfField() : PostEffect(PostEffect::EType::DepthOfField, "Depth of Field")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("DepthOfFieldPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_depthTextureID = glGetUniformLocation(m_shaderID, "depthTexture");

    m_intensityID    = glGetUniformLocation(m_shaderID, "intensity");
    m_blurPlaneID    = glGetUniformLocation(m_shaderID, "blurPlane");

    m_blurPlane = 200.0f;
    m_intensity = 20;

    glUseProgram(m_shaderID);
    glUniform1f (m_blurPlaneID, m_blurPlane);
    glUniform1i (m_intensityID, m_intensity);
    glUseProgram(0);
}

/// \brief Destructor
DepthOfField::~DepthOfField() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void DepthOfField::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture, uint shadowMapTexture)
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
void DepthOfField::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_DepthOfField", &m_bIsActive);

    ImGui::Text("\nBlur plane");
    if(ImGui::SliderFloat("###BlurPlane", &m_blurPlane, 0.0f, 200.0f, "Blur Plane = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_blurPlaneID, m_blurPlane);
        glUseProgram(0);
    }

    ImGui::Text("\nIntensity");
    if(ImGui::SliderInt("###Intensity_dop", &m_intensity, 1, 20))
    {
        glUseProgram(m_shaderID);
        glUniform1i (m_intensityID, m_intensity);
        glUseProgram(0);
    }
}

} // !namespace