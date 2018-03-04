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

/// \file       BoxBlur.cpp
/// \date       04/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/BoxBlur.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
BoxBlur::BoxBlur() : PostEffect(PostEffect::EType::BoxBlur, "Box blur")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("BoxBlurPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_intesityID     = glGetUniformLocation(m_shaderID, "intensity");
    m_intensity      = 3;

    glUseProgram(m_shaderID);
    glUniform1i (m_intesityID, m_intensity);
    glUseProgram(0);
}

/// \brief Destructor
BoxBlur::~BoxBlur() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
void BoxBlur::ApplyEffect(uint colorTexture, uint depthTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
}

/// \brief Called to display the GUI
void BoxBlur::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_BoxBlur", &m_bIsActive);

    ImGui::Text("\nIntensity");
    if(ImGui::SliderInt("###Slider_BoxBlurIntensity", &m_intensity, 3, 20))
    {
        int _intensity = m_intensity;
        if((_intensity & 1) == 0)
        {
            _intensity++;
        }

        glUseProgram(m_shaderID);
        glUniform1i (m_intesityID, _intensity);
        glUseProgram(0);
    }
}

} // !namespace