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

/// \file       DebugLine.cpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/ext.hpp"
#include "Runtime/Rendering/Debug/DebugGizmos.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \namespace debug
namespace debug
{

/// \brief Draw a light bulbe with lines
/// \param position The start point of the line
/// \param color The color of the gizmo
/// \param scale The end point of the line
void DrawLight(glm::vec3 const& position, glm::vec3 const& color, float scale)
{
#ifdef CARDINAL_DEBUG

    glm::vec3 top  (position.x, position.y, position.z + 2.0f * scale);
    glm::vec3 bot  (position.x, position.y, position.z - 2.0f * scale);
    glm::vec3 left (position.x - 1.0f * scale, position.y, position.z);
    glm::vec3 right(position.x + 1.0f * scale, position.y, position.z);
    glm::vec3 front(position.x, position.y + 1.0f * scale, position.z);
    glm::vec3 back (position.x, position.y - 1.0f * scale, position.z);


    glm::vec3 rayLeftStart(left.x - 1.0f,         left.y, left.z);
    glm::vec3 rayLeftEnd  (left.x - 2.0f * scale, left.y, left.z);

    glm::vec3 rayRightStart(right.x + 1.0f,         right.y, right.z);
    glm::vec3 rayRightEnd  (right.x + 2.0f * scale, right.y, right.z);

    glm::vec3 rayFrontStart(front.x, front.y + 1.0f,         front.z);
    glm::vec3 rayFrontEnd  (front.x, front.y + 2.0f * scale, front.z);

    glm::vec3 rayBackStart(back.x, back.y - 1.0f,         back.z);
    glm::vec3 rayBackEnd  (back.x, back.y - 2.0f * scale, back.z);


    DebugManager::AddLine(top, left,  color);
    DebugManager::AddLine(top, right, color);
    DebugManager::AddLine(top, front, color);
    DebugManager::AddLine(top, back,  color);

    DebugManager::AddLine(bot, left,  color);
    DebugManager::AddLine(bot, right, color);
    DebugManager::AddLine(bot, front, color);
    DebugManager::AddLine(bot, back,  color);

    DebugManager::AddLine(right,  back,  color);
    DebugManager::AddLine(right, front,  color);
    DebugManager::AddLine(front, left,   color);
    DebugManager::AddLine(back,  left,   color);

    DebugManager::AddLine(rayLeftStart,  rayLeftEnd,  color);
    DebugManager::AddLine(rayRightStart, rayRightEnd, color);
    DebugManager::AddLine(rayFrontStart, rayFrontEnd, color);
    DebugManager::AddLine(rayBackStart,  rayBackEnd,  color);
#endif

}

} // !namespace

} // !namespace