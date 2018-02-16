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

/// \file       DebugBox.hpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEBUG_BOX_HPP__
#define CARDINAL_ENGINE_DEBUG_BOX_HPP__

#include "Glm/glm/glm.hpp"

/// \namespace cardinal
namespace cardinal
{

namespace debug
{

/// \brief Draw a box in the world
/// \param center The center of the box
/// \param width The width of the box
/// \param color The height of the box
void DrawBox(glm::vec3 const& center, float width, float height, glm::vec3 const& color);

}  // !namespace

} // !namespace

#endif // !CARDINAL_ENGINE_DEBUG_BOX_HPP__