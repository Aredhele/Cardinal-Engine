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

/// \file       Cone.hpp
/// \date       11/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Particle/EmissionShape
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_CONE_HPP__
#define CARDINAL_ENGINE_CONE_HPP__

#include "Runtime/Rendering/Particle/EmissionShape/EmissionShape.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class Cone
/// \brief Cone emission shape
class Cone : public EmissionShape
{
public:

    /// \brief Constuctor
    /// \param radius The base radius of the cone
    /// \param topRadius The top radius
    Cone(float radius, float topRadius);

    /// \brief Called to draw the emission shape
    /// \param systemPosition The position of the particle system
    void DrawGizmo(glm::vec3 const& systemPosition) final;

    /// \brief Returns a random position in the base of the emission shape
    /// \param systemPosition The position of the particle system
    /// \return The position
    glm::vec3 GetStartPosition(glm::vec3 const& systemPosition) const final;

    /// \brief Computes the start direction of a particles
    /// \param particlePosition The position of the particle
    /// \param systemPosition The position of the particle system
    /// \return The new direction
    glm::vec3 GetDirection(glm::vec3 const& particlePosition, glm::vec3 const& systemPosition) const final;

    /// \brief Called when the object is inspected
    void OnInspectorGUI() final;

private:

    float     m_lenght;
    float     m_radius;
    float     m_topRadius;
    glm::vec3 m_position;
};

} // !namespace

#endif // !CARDINAL_ENGINE_CONE_HPP__