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

/// \file       Plane.cpp
/// \date       13/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Particle/EmissionShape
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/glm.hpp"
#include "Glm/glm/ext.hpp"
#include "ImGUI/Header/ImGUI/imgui.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/Particle/EmissionShape/Plane.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constuctor
/// \param lenght The lenght of the plane
/// \param width The width of the plane
Plane::Plane(float lenght, float width)
{
    m_lenght = lenght;
    m_width  = width;

    inspectorName = "Plane shape";
}

/// \brief Called to draw the emission shape
/// \param systemPosition The position of the particle system
void Plane::DrawGizmo(glm::vec3 const& systemPosition)
{
    glm::vec3 P1 = glm::vec3(systemPosition.x - (m_lenght / 2.0f), systemPosition.y - (m_width / 2.0f), systemPosition.z);
    glm::vec3 P2 = glm::vec3(systemPosition.x + (m_lenght / 2.0f), systemPosition.y - (m_width / 2.0f), systemPosition.z);
    glm::vec3 P3 = glm::vec3(systemPosition.x + (m_lenght / 2.0f), systemPosition.y + (m_width / 2.0f), systemPosition.z);
    glm::vec3 P4 = glm::vec3(systemPosition.x - (m_lenght / 2.0f), systemPosition.y + (m_width / 2.0f), systemPosition.z);

    cardinal::debug::DrawLine(P1, P2, glm::vec3(1.0f, 0.0f, 0.0f));
    cardinal::debug::DrawLine(P2, P3, glm::vec3(1.0f, 0.0f, 0.0f));
    cardinal::debug::DrawLine(P3, P4, glm::vec3(1.0f, 0.0f, 0.0f));
    cardinal::debug::DrawLine(P4, P1, glm::vec3(1.0f, 0.0f, 0.0f));
}

/// \brief Returns a random position in the base of the emission shape
/// \param systemPosition The position of the particle system
/// \return The position
glm::vec3 Plane::GetStartPosition(glm::vec3 const& systemPosition) const
{
    glm::vec2 position2D = glm::linearRand(glm::vec2(0.0f, 0.0f), glm::vec2(m_lenght, m_width));
    return glm::vec3(systemPosition.x + position2D.x,
                     systemPosition.y + position2D.y, systemPosition.z);
}

/// \brief Computes the start direction of a particles
/// \param systemPosition The position of the particle system
/// \return The new direction
glm::vec3 Plane::GetDirection(glm::vec3 const& particlePosition, glm::vec3 const& systemPosition) const
{
    return glm::vec3(0.0f, 0.0f, 1.0f);
}

/// \brief Called when the object is inspected
void Plane::OnInspectorGUI()
{
    if(ImGui::CollapsingHeader(inspectorName.c_str()))
    {
        ImGui::InputFloat("Lenght###Plane_BaseRadius",  &m_lenght,0.1f, 0.5f);
        ImGui::InputFloat("Width ###Plane_TopRadius",   &m_width, 0.1f, 1.0f);

        ImGui::TextDisabled(  "Position : %f %f %f", m_position.x, m_position.y, m_position.z);
    }
}

} // !namespace