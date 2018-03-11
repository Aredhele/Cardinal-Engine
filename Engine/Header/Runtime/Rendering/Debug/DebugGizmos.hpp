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

/// \file       DebugGizmos.hpp
/// \date       20/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEBUG_GIZMOS_HPP__
#define CARDINAL_ENGINE_DEBUG_GIZMOS_HPP__

#include "Glm/glm/glm.hpp"

/// \namespace cardinal
namespace cardinal
{

namespace debug
{

/// \brief Draw a directional light with lines
/// \param position The start point of the line
/// \param direction The direction of the light
/// \param color The color of the gizmo
/// \param scale The end point of the line
void DrawDirectionalLight(glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& color, float scale);

/// \brief Draw a point light with lines
/// \param position The start point of the line
/// \param color The color of the gizmo
/// \param resolution The number of points per circle
/// \param range The range of the light
/// \param scale The end point of the line
void DrawPointLight(glm::vec3 const& position, glm::vec3 const& color, int resolution, float range, float scale);

/// \brief Draw a cone in the world
/// \param position The start point of the cone
/// \param radius The base radius of the cone
/// \param angle The angle of the cone
/// \param lenght The lenght of the cone
/// \param color The color of the line
void DrawCone(glm::vec3 const& position, float radius, float angle, float lenght, glm::vec3 const& color);

}  // !namespace

} // !namespace

#endif // !CARDINAL_ENGINE_DEBUG_GIZMOS_HPP__