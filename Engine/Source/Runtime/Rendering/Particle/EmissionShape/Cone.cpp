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

#include "Runtime/Rendering/Particle/EmissionShape/Cone.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Returns a random position in the base of the emission shape
/// \return The position
glm::vec3 Cone::GetStartPosition() const
{
    return glm::vec3();
}

/// \brief Perturbs a velocity vector from a position and depending the shape
/// \return The new velocity
glm::vec3 Cone::Perturb(glm::vec3 const &initialVelocity, glm::vec3 const &position) const
{
    return glm::vec3();
}

} // !namespace