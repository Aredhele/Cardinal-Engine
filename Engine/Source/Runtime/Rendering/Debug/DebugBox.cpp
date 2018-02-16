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

/// \file       DebugBox.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/ext.hpp"
#include "Runtime/Rendering/Debug/DebugBox.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \namespace debug
namespace debug
{

/// \brief Draw a box in the world
/// \param center The center of the box
/// \param width The width of the box
/// \param color The height of the box
void DrawBox(glm::vec3 const& center, float width, float height, glm::vec3 const& color)
{
    float halfWidth  = width  / 2.0f;
    float halfHeight = height / 2.0f;

    glm::vec3 A(center.x - halfWidth, center.y + halfWidth, center.z - halfHeight);
    glm::vec3 B(center.x + halfWidth, center.y + halfWidth, center.z - halfHeight);
    glm::vec3 C(center.x + halfWidth, center.y - halfWidth, center.z - halfHeight);
    glm::vec3 D(center.x - halfWidth, center.y - halfWidth, center.z - halfHeight);
    glm::vec3 E(center.x - halfWidth, center.y + halfWidth, center.z + halfHeight);
    glm::vec3 F(center.x + halfWidth, center.y + halfWidth, center.z + halfHeight);
    glm::vec3 G(center.x + halfWidth, center.y - halfWidth, center.z + halfHeight);
    glm::vec3 H(center.x - halfWidth, center.y - halfWidth, center.z + halfHeight);

    DebugManager::AddLine(A, B, color);
    DebugManager::AddLine(B, C, color);
    DebugManager::AddLine(C, D, color);
    DebugManager::AddLine(D, A, color);

    DebugManager::AddLine(A, E, color);
    DebugManager::AddLine(B, F, color);
    DebugManager::AddLine(C, G, color);
    DebugManager::AddLine(D, H, color);

    DebugManager::AddLine(E, F, color);
    DebugManager::AddLine(F, G, color);
    DebugManager::AddLine(G, H, color);
    DebugManager::AddLine(H, E, color);
}

} // !namespace

} // !namespace