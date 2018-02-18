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

/// \file       DebugLine.hpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEBUG_RAY_HPP__
#define CARDINAL_ENGINE_DEBUG_RAY_HPP__

#include "Glm/glm/glm.hpp"

/// \namespace cardinal
namespace cardinal
{

namespace debug
{

/// \brief Draw a ray from start to start + dir
/// \param start The start point of the ray
/// \param dir   The direction of the ray
/// \param color The color of the line
void DrawRay(glm::vec3 const& start, glm::vec3 const& dir, glm::vec3 const& color);

}  // !namespace

} // !namespace

#endif // !CARDINAL_ENGINE_DEBUG_RAY_HPP__