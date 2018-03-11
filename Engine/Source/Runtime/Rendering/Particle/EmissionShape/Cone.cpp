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

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/Particle/EmissionShape/Cone.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constuctor
/// \param radius The base radius of the cone
/// \param angle The angle of the cone
Cone::Cone(float radius, float angle)
{
    m_radius   = radius;
    m_angle    = angle;
    m_lenght   = 5.0f;
}

/// \brief Called to draw the emission shape
/// \param systemPosition The position of the particle system
void Cone::DrawGizmo(glm::vec3 const& systemPosition)
{
    cardinal::debug::DrawCone(systemPosition, m_radius, m_angle, m_lenght, glm::vec3(1.0, 0.0f, 0.0f));
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
glm::vec3 Cone::GetDirection(glm::vec3 const& systemPosition) const
{
    float baseRadius = m_radius;

    float x  = cosf(m_angle) * m_lenght;
    float y  = sinf(m_angle) * m_lenght;

    glm::vec2 offset = glm::vec2(x, y) - glm::vec2(systemPosition.x, systemPosition.y);
    float topRadius  = glm::sqrt(offset.x * offset.x + offset.y * offset.y);

    Logger::LogInfo("Base radius = %f", baseRadius);
    Logger::LogInfo("Top  radius = %f", topRadius);

    return glm::vec3();
}

} // !namespace