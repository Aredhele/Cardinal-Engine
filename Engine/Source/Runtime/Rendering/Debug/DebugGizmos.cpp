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

    glm::vec3 arrowStart1(bot.x, bot.y, bot.z - 1.0f);
    glm::vec3 arrowEnd1  (arrowStart1 + (glm::normalize(-position)) - 2.0f * scale);

    glm::vec3 arrowStart2(bot.x - 1.0f, bot.y - 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd2  (arrowStart2 + glm::normalize(-position + glm::vec3(-1.0f, -1.0f, 0.0f)) - 2.0f * scale);

    glm::vec3 arrowStart3(bot.x + 1.0f, bot.y + 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd3  (arrowStart3 + glm::normalize(-position + glm::vec3(1.0f, 1.0f, 0.0f)) - 2.0f * scale);

    glm::vec3 arrowStart4(bot.x + 1.0f, bot.y - 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd4  (arrowStart4 + glm::normalize(-position + glm::vec3(1.0f, -1.0f, 0.0f)) - 2.0f * scale);

    glm::vec3 arrowStart5(bot.x - 1.0f, bot.y + 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd5  (arrowStart5 + glm::normalize(-position + glm::vec3(-1.0f, 1.0f, 0.0f)) - 2.0f * scale);

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

    DebugManager::AddLine(arrowStart1, arrowEnd1, color);
    DebugManager::AddLine(arrowStart2, arrowEnd2, color);
    DebugManager::AddLine(arrowStart3, arrowEnd3, color);
    DebugManager::AddLine(arrowStart4, arrowEnd4, color);
    DebugManager::AddLine(arrowStart5, arrowEnd5, color);
#endif

}

} // !namespace

} // !namespace