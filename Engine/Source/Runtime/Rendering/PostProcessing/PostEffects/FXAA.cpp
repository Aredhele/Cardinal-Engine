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

/// \file       FXAA.cpp
/// \date       06/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include <iostream>
#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/FXAA.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
FXAA::FXAA() : PostEffect(PostEffect::EType::FXAA, "FXAA")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("FXAAPostProcess");

    // Getting uniforms
    m_colorTextureID   = glGetUniformLocation(m_shaderID, "colorTexture");
    m_fxaaSpanID       = glGetUniformLocation(m_shaderID, "FXAASpan");
    m_fxaaReduceMulID  = glGetUniformLocation(m_shaderID, "FXAAReduceMul");
    m_fxaaReduceMinID  = glGetUniformLocation(m_shaderID, "FXAAReduceMin");

    m_fxaaSpan      = 8.0f;
    m_fxaaReduceMul = 1.0f / 8.0f;
    m_fxaaReduceMin = 1.0f / 128.0f;

    glUseProgram(m_shaderID);
    glUniform1f (m_fxaaSpanID,      m_fxaaSpan);
    glUniform1f (m_fxaaReduceMulID, m_fxaaReduceMul);
    glUniform1f (m_fxaaReduceMinID, m_fxaaReduceMin);
    glUseProgram(0);
}

/// \brief Destructor
FXAA::~FXAA() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void FXAA::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture,
                       uint shadowMapTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
}

/// \brief Called to draw the GUI
void FXAA::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_FXAA", &m_bIsActive);

    ImGui::Text("\nSpan");
    if(ImGui::SliderFloat("###Span_fxaa", &m_fxaaSpan, 0.0f, 20.0f, "Span = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_fxaaSpanID, m_fxaaSpan);
        glUseProgram(0);
    }

    ImGui::Text("\nReduce mul");
    if(ImGui::SliderFloat("###RMul_fxaa", &m_fxaaReduceMul, 0.0f, 1.0f, "Reduce mul = %.5f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_fxaaReduceMulID, m_fxaaReduceMul);
        glUseProgram(0);
    }

    ImGui::Text("\nReduce min");
    if(ImGui::SliderFloat("###RMin_fxaa", &m_fxaaReduceMin, 0.0f, 1.0f, "Reduce max = %.5f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_fxaaReduceMinID, m_fxaaReduceMin);
        glUseProgram(0);
    }
}

} // !namespace