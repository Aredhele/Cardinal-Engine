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

/// \file       EmissionShape.hpp
/// \date       11/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Particle/EmissionShape
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_EMISSION_SHAPE_HPP__
#define CARDINAL_ENGINE_EMISSION_SHAPE_HPP__

#include "Glm/glm/vec3.hpp"
#include "Runtime/Rendering/Hierarchy/Inspector.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class EmissionShape
/// \brief Interface for all emission shapes
class EmissionShape : public Inspector
{
public:

    /// \brief Called to draw the emission shape
    /// \param systemPosition The position of the particle system
    virtual void DrawGizmo(glm::vec3 const& systemPosition) = 0;

    /// \brief Returns a random position in the base of the emission shape
    /// \param systemPosition The position of the particle system
    /// \return The position
    virtual glm::vec3 GetStartPosition(glm::vec3 const& systemPosition) const = 0;

    /// \brief Computes the start direction of a particles
    /// \param particlePosition The position of the particle
    /// \param systemPosition The position of the particle system
    /// \return The new direction
    virtual glm::vec3 GetDirection(glm::vec3 const& particlePosition, glm::vec3 const& systemPosition) const = 0;
};

} // !namespace

#endif // !CARDINAL_ENGINE_EMISSION_SHAPE_HPP__