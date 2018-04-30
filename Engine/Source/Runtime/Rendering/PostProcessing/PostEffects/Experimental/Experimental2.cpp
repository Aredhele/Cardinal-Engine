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

/// \file       Experimental1.cpp
/// \date       05/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include <Header/Runtime/Rendering/Texture/TextureLoader.hpp>
#include <Header/Runtime/Rendering/Texture/TextureManager.hpp>
#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Experimental/Experimental2.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Experimental2::Experimental2() : PostEffect(PostEffect::EType::Experimental2, "Experimental 2")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("Experimental2PostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_whiteNoiseTextureID = glGetUniformLocation(m_shaderID, "whiteNoiseTexture");
    m_timeID = glGetUniformLocation(m_shaderID, "time");
    m_intensityID = glGetUniformLocation(m_shaderID, "intensity");
}

/// \brief Destructor
Experimental2::~Experimental2() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void Experimental2::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture,
                                uint shadowMapTexture)
{
    timer +=0.01f;
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture   (GL_TEXTURE_2D, TextureManager::GetTextureID("WhiteNoise"));
    glUniform1i    (m_whiteNoiseTextureID, 1);
    glUniform1f    (m_timeID, timer);
    glUniform1f    (m_intensityID, m_intensity);
}

/// \brief Called to draw the GUI
void Experimental2::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_Experimental2", &m_bIsActive);

    ImGui::Text("\nIntensity");
    if(ImGui::SliderFloat("###Slider_Experimental2Intensity", &m_intensity, 0.0, 1.0))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_intensityID, m_intensity);
        glUseProgram(0);
    }
}

} // !namespace
