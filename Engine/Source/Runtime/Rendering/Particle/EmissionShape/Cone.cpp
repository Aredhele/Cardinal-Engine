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

/// \file       Cone.cpp
/// \date       11/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Particle/EmissionShape
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/glm.hpp"
#include "Glm/glm/ext.hpp"
#include "ImGUI/Header/ImGUI/imgui.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/Particle/EmissionShape/Cone.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constuctor
/// \param radius The base radius of the cone
/// \param topRadius The top radius
Cone::Cone(float radius, float topRadius)
{
    m_radius    = radius;
    m_topRadius = topRadius;
    m_lenght    = 15.0f;

    inspectorName = "Cone shape";
}

/// \brief Called to draw the emission shape
/// \param systemPosition The position of the particle system
void Cone::DrawGizmo(glm::vec3 const& systemPosition)
{
    cardinal::debug::DrawCone(systemPosition, m_radius, m_topRadius, m_lenght, glm::vec3(1.0, 0.0f, 0.0f));
}

/// \brief Returns a random position in the base of the emission shape
/// \param systemPosition The position of the particle system
/// \return The position
glm::vec3 Cone::GetStartPosition(glm::vec3 const& systemPosition) const
{
    glm::vec2 position2D = glm::diskRand(m_radius);
    return glm::vec3(systemPosition.x + position2D.x,
                     systemPosition.y + position2D.y, systemPosition.z);
}

/// \brief Computes the start direction of a particles
/// \param systemPosition The position of the particle system
/// \return The new direction
glm::vec3 Cone::GetDirection(glm::vec3 const& particlePosition, glm::vec3 const& systemPosition) const
{
    float radiusRatio    = m_topRadius / m_radius;
    glm::vec2 direction  = (particlePosition - systemPosition) * radiusRatio;
    glm::vec3 endPoint   = glm::vec3(direction.x, direction.y, systemPosition.z + m_lenght);

    glm::vec3 dir = glm::normalize(particlePosition - systemPosition) * m_topRadius;
    glm::vec3 A   = particlePosition;
    glm::vec3 B   = systemPosition + glm::vec3(dir.x, dir.y, m_lenght);

    return glm::normalize(B - A);
}

/// \brief Called when the object is inspected
void Cone::OnInspectorGUI()
{
    if(ImGui::CollapsingHeader(inspectorName.c_str()))
    {
        ImGui::InputFloat("Base radius###Cone_BaseRadius",  &m_radius,    0.1f, 0.5f);
        ImGui::InputFloat("Top radius###Cone_TopRadius",    &m_topRadius, 0.1f, 1.0f);

        ImGui::TextDisabled("\nLenght   : %f", m_lenght);
        ImGui::TextDisabled(  "Position : %f %f %f", m_position.x, m_position.y, m_position.z);
    }
}

} // !namespace