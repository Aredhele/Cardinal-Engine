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

#ifndef CARDINAL_ENGINE_PLANE_HPP__
#define CARDINAL_ENGINE_PLANE_HPP__

#include "Runtime/Rendering/Particle/EmissionShape/EmissionShape.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class Plane
/// \brief Plane emission shape
class Plane : public EmissionShape
{
public:

    /// \brief Constuctor
    /// \param lenght The lenght of the plane
    /// \param width The width of the plane
    Plane(float lenght, float width);

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
    float     m_width;
    glm::vec3 m_position;
};

} // !namespace

#endif // !CARDINAL_ENGINE_PLANE_HPP__