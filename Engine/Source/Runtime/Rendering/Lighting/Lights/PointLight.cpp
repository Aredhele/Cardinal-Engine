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

/// \file       PointLight.cpp
/// \date       24/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting/Lights
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/vec4.hpp"
#include "ImGUI/Header/ImGUI/imgui.h"
#include "Runtime/Rendering/Lighting/Lights/PointLight.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
PointLight::PointLight()
{
    m_range       = 10;
    m_intensity   = 1.0f;
    m_position    = glm::vec3(0.0f);
    m_color       = glm::vec3(1.0f);
    inspectorName = "Point Light";
}

/// \brief Destructor
PointLight::~PointLight() // NOLINT
{
    // None
}

/// \brief Sets the range of the light (in engine unit)
/// \param range The new range
void PointLight::SetRange(float range)
{
    m_range = range;
}

/// \brief Sets the intensity of the light
/// \param intensity The new intensity
void PointLight::SetIntensity(float intensity)
{
    m_intensity = intensity;
}

/// \brief Sets the position of the light
/// \param position The new position
void PointLight::SetPosition(glm::vec3 const& position)
{
    m_position = position;
}

/// \brief Sets the color of the light
/// \param color The new color
void PointLight::SetColor(glm::vec3 const& color)
{
    m_color = color;
}

/// \brief  Returns the range of the light
/// \return The range of the light
float PointLight::GetRange() const
{
    return m_range;
}

/// \brief Return the intensity of the light
/// \return The intensity of the light
float PointLight::GetIntensity() const
{
    return m_intensity;
}

/// \brief  Returns the position of the light
/// \return The position of the light
glm::vec3 const& PointLight::GetPosition() const
{
    return m_position;
}

/// \brief Returns the color of the light
/// \return The color of the light
glm::vec3 const &PointLight::GetColor() const
{
    return m_color;
}

/// \brief Called when the object is inspected
void PointLight::OnInspectorGUI()
{
    ImGui::Text(inspectorName.c_str());
    ImGui::InputFloat("Light range###Point_lightRange",         &m_range,     0.01f, 0.1f);
    ImGui::InputFloat("Light intensity###Point_lightIntensity", &m_intensity, 0.01f, 0.1f);

    glm::vec4 lcolor(m_color.x, m_color.y, m_color.z, 1.0f);

    ImGui::Text("\nLight color");
    if(ImGui::ColorEdit4("###Point_lcolor", &lcolor[0]))
    {
        m_color.x = lcolor.x;
        m_color.y = lcolor.y;
        m_color.z = lcolor.z;
    }

    ImGui::InputFloat3("Position###Point_position", &m_position[0], 3);
}

} // !namespace