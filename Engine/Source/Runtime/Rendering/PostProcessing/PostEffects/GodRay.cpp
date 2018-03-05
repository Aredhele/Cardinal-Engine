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


#include <iostream>
#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Lighting/LightManager.hpp"
#include "Runtime/Rendering/Lighting/Lights/DirectionalLight.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/GodRay.hpp"
#include <Header/Runtime/Rendering/RenderingEngine.hpp>
#include <Header/Runtime/Core/Debug/Logger.hpp>
/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
GodRay::GodRay() : PostEffect(PostEffect::EType::GodRay, "God ray")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("GodRayPostProcess");

    // Getting uniforms
    m_colorTextureID           = glGetUniformLocation(m_shaderID, "colorTexture");
    m_depthTextureID           = glGetUniformLocation(m_shaderID, "depthTexture");
    m_lightScatteringTextureID = glGetUniformLocation(m_shaderID, "lightScatteringTexture");

    m_decayID           = glGetUniformLocation(m_shaderID, "decay");
    m_weightID          = glGetUniformLocation(m_shaderID, "weight");
    m_densityID         = glGetUniformLocation(m_shaderID, "density");
    m_exposureID        = glGetUniformLocation(m_shaderID, "exposure");
    m_sampleCountID     = glGetUniformLocation(m_shaderID, "sampleCount");
    m_lightPosition2DID = glGetUniformLocation(m_shaderID, "lightPosition2D");

    m_decay       = 0.96815;
    m_weight      = 0.587;
    m_density     = 0.926;
    m_exposure    = 0.2f;
    m_sampleCount = 128;

    glUseProgram(m_shaderID);
    glUniform1f (m_decayID, m_decay);
    glUniform1f (m_weightID, m_weight);
    glUniform1f (m_densityID, m_density);
    glUniform1f (m_exposureID, m_exposure);
    glUniform1i (m_sampleCountID, m_sampleCount);
    glUniform2f (m_lightPosition2DID, 0.0f, 0.0f);
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
/// \param lightScatteringTexture The result of the light scattering pass
void GodRay::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, colorTexture);
    glUniform1i    (m_colorTextureID, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture  (GL_TEXTURE_2D, depthTexture);
    glUniform1i    (m_depthTextureID, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture  (GL_TEXTURE_2D, lightScatteringTexture);
    glUniform1i    (m_lightScatteringTextureID, 2);

    if(LightManager::GetDirectionalLight() != nullptr)
    {
        // Projection on 2D screen
        glm::vec3 position   = LightManager::GetDirectionalLight()->GetPosition();
        glm::mat4 View       = RenderingEngine::GetViewMatrix();
        glm::mat4 Projection = RenderingEngine::GetProjectionMatrix();

        glm::vec4 clipSpacePos = Projection * (View * glm::vec4(position, 1.0f));
        glm::vec3 subClip      = glm::vec3(clipSpacePos.x, clipSpacePos.y, clipSpacePos.z);

        glm::vec3 ndcSpacePos    = subClip / clipSpacePos.w;
        glm::vec2 subNdc         = glm::vec2(ndcSpacePos.x, ndcSpacePos.y);
        glm::vec2 windowSpacePos = ((subNdc + glm::vec2(1.0f, 1.0f)) / 2.0f) * glm::vec2(1600.0f, 900.0f) + glm::vec2(0.0f, 0.0f);

        glUniform2f(m_lightPosition2DID, windowSpacePos.x / 1600.0f, windowSpacePos.y / 900.0f);
    }
}

/// \brief Called to draw the GUI
void GodRay::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_GodRay", &m_bIsActive);

    ImGui::Text("\nIntensity");
    if(ImGui::SliderFloat("###Density_GodRay", &m_density, 0.0f, 2.0f, "Intensity = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_densityID, m_density);
        glUseProgram(0);
    }

    ImGui::Text("\nWeight");
    if(ImGui::SliderFloat("###Weight_GodRay", &m_weight, 0.0f, 0.1f, "Weight = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_weightID, m_weight);
        glUseProgram(0);
    }

    ImGui::Text("\nDecay");
    if(ImGui::SliderFloat("###Decay_GodRay", &m_decay, 0.8, 1, "Decay = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_decayID, m_decay);
        glUseProgram(0);
    }

    ImGui::Text("\nExposure");
    if(ImGui::SliderFloat("###Exposure_GodRay", &m_exposure, 0, 1, "Exposure = %.3f"))
    {
        glUseProgram(m_shaderID);
        glUniform1f (m_exposureID, m_exposure);
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