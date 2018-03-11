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

/// \file       ParticleShader.cpp
/// \date       10/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader/Built-in/Particle
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "ImGUI/Header/ImGUI/imgui.h"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Particle/ParticleShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
ParticleShader::ParticleShader()
{
    m_shaderID = ShaderManager::GetShaderID("ParticleShader");

    m_VPID          = glGetUniformLocation((uint)m_shaderID, "VP");
    m_cameraUpID    = glGetUniformLocation((uint)m_shaderID, "cameraUpWorld");
    m_cameraRightID = glGetUniformLocation((uint)m_shaderID, "cameraRightWorld");

    inspectorName = "Particle Shader";
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void ParticleShader::Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    glUseProgram      ((uint)m_shaderID);

    glm::vec3 right = glm::vec3(V[0][0], V[1][0], V[2][0]);
    glm::vec3 up    = glm::vec3(V[0][1], V[1][1], V[2][1]);
    glm::mat4 PV    = P * V;

    glUniformMatrix4fv(m_VPID, 1, GL_FALSE, &PV[0][0]);
    glUniform3f       (m_cameraUpID,    up.x, up.y, up.z);
    glUniform3f       (m_cameraRightID, right.x, right.y, right.z);
}

/// \brief Restore the pipeline state
void ParticleShader::End()
{
    // None
}

/// \brief Called when the object is inspected
void ParticleShader::OnInspectorGUI()
{
    if(ImGui::CollapsingHeader("Material"))
    {
        ImGui::Text(inspectorName.c_str());

        ImGui::TextDisabled("Shader ID : %d", m_shaderID);
        ImGui::TextDisabled("Uniform VP ID          : %d", m_VPID);
        ImGui::TextDisabled("Uniform CameraUp    ID : %d", m_cameraUpID);
        ImGui::TextDisabled("Uniform CameraRight ID : %d", m_cameraRightID);
    }
}

} // !namespace



