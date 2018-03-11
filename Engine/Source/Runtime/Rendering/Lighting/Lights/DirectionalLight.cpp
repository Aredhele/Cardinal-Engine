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

/// \file       DirectionalLight.cpp
/// \date       23/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "ImGUI/Header/ImGUI/imgui.h"
#include "Glm/glm/gtc/matrix_transform.hpp"
#include "Runtime/Rendering/Mesh/Cube.hpp"
#include "Runtime/Rendering/Lighting/Lights/DirectionalLight.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
DirectionalLight::DirectionalLight()
{
    // Basics settings
    SetPosition (glm::vec3(16.0f, 16.0f, 16.0f));
    SetDirection(glm::vec3(-0.5f, -0.5f, -0.5f));
    SetLightIntensity  (0.8f);
    SetAmbientIntensity(0.3f);
    SetLightColor  (glm::vec3(1.0f, 1.0f, 1.0f));
    SetAmbientColor(glm::vec3(1.0f, 1.0f, 1.0f));

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), &Cube::s_vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    m_elementsCount = 108;
    inspectorName   = "Directional Light";
}

/// \brief Sets the light intensity
/// \param intensity The intensity of the light
void DirectionalLight::SetLightIntensity(float intensity)
{
    m_lightIntensity = intensity;
}

/// \brief Sets the intensity of the ambient
/// \param intensity The intensity of the ambient
void DirectionalLight::SetAmbientIntensity(float intensity)
{
    m_ambientIntensity = intensity;
}

/// \brief Sets the position of the light
/// \param position The new position
void DirectionalLight::SetPosition(glm::vec3 const &position)
{
    m_position = position;
    m_model    = glm::mat4(1.0f);
    m_model    = glm::translate(m_model, position);
}

/// \brief Sets the direction of the light
/// \param direction The new direction
void DirectionalLight::SetDirection(glm::vec3 const& direction)
{
    m_direction = direction;
}

/// \brief Sets the light color
/// \param color The  new color
void DirectionalLight::SetLightColor(glm::vec3 const &color)
{
    m_lightColor = color;
}

/// \brief Sets the ambient color
/// \param color The new color
void DirectionalLight::SetAmbientColor(glm::vec3 const &color)
{
    m_ambientColor = color;
}

/// \brief Returns the light intensity
/// \return The intensity of the light
float DirectionalLight::GetLightIntensity() const
{
    return m_lightIntensity;
}

/// \brief Returns the ambient intensity
/// \return The ambient intensity
float DirectionalLight::GetAmbientIntensity() const
{
    return m_ambientIntensity;
}

/// \brief Returns the position of the light
/// \return The current position
glm::vec3 const &DirectionalLight::GetPosition() const
{
    return m_position;
}

/// \brief Returns the direction of the light
/// \param The direction of the light
glm::vec3 const& DirectionalLight::GetDirection() const
{
    return m_direction;
}

/// \brief Returns the color of the light
/// \return The color of the light
glm::vec3 const &DirectionalLight::GetLightColor() const
{
    return m_lightColor;
}

/// \brief Returns the color of the ambient
/// \return The ambient color
glm::vec3 const &DirectionalLight::GetAmbientColor() const
{
    return m_ambientColor;
}

/// \brief Called when the object is inspected
void DirectionalLight::OnInspectorGUI()
{
    ImGui::Text(inspectorName.c_str());
    ImGui::InputFloat("Light intensity###Directional_lightIntensity",     &m_lightIntensity,   0.01f, 0.1f);
    ImGui::InputFloat("Ambient intensity###Directional_ambientIntensity", &m_ambientIntensity, 0.01f, 0.1f);

    glm::vec4 lcolor  (m_lightColor.x,   m_lightColor.y,   m_lightColor.z,   1.0f);
    glm::vec4 aambient(m_ambientColor.x, m_ambientColor.y, m_ambientColor.z, 1.0f);

    ImGui::Text("\nLight color");
    if(ImGui::ColorEdit4("###Dir_lcolor", &lcolor[0]))
    {
        m_lightColor.x = lcolor.x;
        m_lightColor.y = lcolor.y;
        m_lightColor.z = lcolor.z;
    }

    ImGui::Text("\nAmbient color");
    if(ImGui::ColorEdit4("###Dir_acolor", &aambient[0]))
    {
        m_ambientColor.x = aambient.x;
        m_ambientColor.y = aambient.y;
        m_ambientColor.z = aambient.z;
    }

    ImGui::InputFloat3("Position###Dir_position", &m_position[0], 3);
    ImGui::InputFloat3("Direction###Dir_direction", &m_direction[0], 3);

    ImGui::TextDisabled("\nVAO : %u", m_vao);
    ImGui::TextDisabled(  "VBO : %u",m_vbo);
}

} // !namespace