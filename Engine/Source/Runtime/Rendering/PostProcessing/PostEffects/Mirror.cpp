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

/// \file       Mirror.cpp
/// \date       02/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO
#include <iostream>
#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Mirror.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Mirror::Mirror() : PostEffect(PostEffect::EType::Mirror, "Mirror")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("MirrorPostProcess");

    // Getting uniforms
    m_colorTextureID = glGetUniformLocation(m_shaderID, "colorTexture");
    m_mirrorXID      = glGetUniformLocation(m_shaderID, "bMirrorX");
    m_mirrorYID      = glGetUniformLocation(m_shaderID, "bMirrorY");

    m_mirrorX = false;
    m_mirrorY = false;

    glUseProgram(m_shaderID);
    glUniform1i (m_mirrorXID, 0);
    glUniform1i (m_mirrorYID, 0);
    glUseProgram(0);
}

/// \brief Destructor
Mirror::~Mirror() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
void Mirror::ApplyEffect(uint colorTexture, uint depthTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);
}

/// \brief Called to draw the GUI
void Mirror::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_Mirror", &m_bIsActive);

    if(ImGui::Checkbox("Mirror X", &m_mirrorX))
    {
        glUseProgram   (m_shaderID);
        if(m_mirrorX) glUniform1i(m_mirrorXID, 1);
        else          glUniform1i(m_mirrorXID, 0);
    }

    if(ImGui::Checkbox("Mirror Y", &m_mirrorY))
    {
        glUseProgram   (m_shaderID);
        if(m_mirrorY) glUniform1i(m_mirrorYID, 1);
        else          glUniform1i(m_mirrorYID, 0);
    }
}

} // !namespace