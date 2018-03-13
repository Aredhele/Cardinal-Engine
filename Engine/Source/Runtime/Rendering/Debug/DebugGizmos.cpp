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

#ifndef _USE_MATH_DEFINES
#	define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <vector>
#include "Glm/glm/ext.hpp"
#include "Runtime/Rendering/Debug/DebugGizmos.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \namespace debug
namespace debug
{

/// \brief Draw a directional light with lines
/// \param position The start point of the line
/// \param direction The direction of the light
/// \param color The color of the gizmo
/// \param scale The end point of the line
void DrawDirectionalLight(glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& color, float scale)
{
#ifdef CARDINAL_DEBUG
    if(!DebugManager::IsGizmoEnabled(DebugManager::EGizmo::DirectionalLight))
    {
        return;
    }

    glm::vec3 dir = glm::normalize(direction) * 10.0f;
    glm::vec3 top  (position.x, position.y, position.z + 2.0f * scale);
    glm::vec3 bot  (position.x, position.y, position.z - 2.0f * scale);
    glm::vec3 left (position.x - 1.0f * scale, position.y, position.z);
    glm::vec3 right(position.x + 1.0f * scale, position.y, position.z);
    glm::vec3 front(position.x, position.y + 1.0f * scale, position.z);
    glm::vec3 back (position.x, position.y - 1.0f * scale, position.z);

    glm::vec3 arrowStart1(bot.x, bot.y, bot.z - 1.0f);
    glm::vec3 arrowEnd1  (arrowStart1 + dir * glm::normalize(arrowStart1));

    glm::vec3 arrowStart2(bot.x - 1.0f, bot.y - 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd2  (arrowStart2 + dir * glm::normalize(arrowStart2));

    glm::vec3 arrowStart3(bot.x + 1.0f, bot.y + 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd3  (arrowStart3 + dir * glm::normalize(arrowStart3));

    glm::vec3 arrowStart4(bot.x + 1.0f, bot.y - 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd4  (arrowStart4 + dir * glm::normalize(arrowStart4));

    glm::vec3 arrowStart5(bot.x - 1.0f, bot.y + 1.0f, bot.z - 1.0f);
    glm::vec3 arrowEnd5  (arrowStart5 + dir * glm::normalize(arrowStart5));

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

/// \brief Draw a point light with lines
/// \param position The start point of the line
/// \param color The color of the gizmo
/// \param resolution The number of points per circle
/// \param range The range of the light
/// \param scale The end point of the line
void DrawPointLight(glm::vec3 const& position, glm::vec3 const& color, int resolution, float range, float scale)
{
#ifdef CARDINAL_DEBUG
    if(!DebugManager::IsGizmoEnabled(DebugManager::EGizmo::PointLight))
    {
        return;
    }

    // Compute spherical coordinates
    int pointCount = static_cast<int>(resolution * scale); // NOLINT
    float alpha    = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

    std::vector<glm::vec3> pointsZ;
    std::vector<glm::vec3> pointsY;
    for (int nPoint = 0; nPoint < pointCount; ++nPoint)
    {
        float x1 = position.x + glm::cos(alpha * nPoint) * range;
        float y1 = position.y + glm::sin(alpha * nPoint) * range;
        float z1 = position.z;

        float x2 = position.x;
        float y2 = position.y + glm::sin(alpha * nPoint) * range;
        float z2 = position.z + glm::cos(alpha * nPoint) * range;

        pointsZ.emplace_back(x1, y1, z1);
        pointsY.emplace_back(x2, y2, z2);

        if(nPoint != 0)
        {
            DebugManager::AddLine(pointsZ[nPoint - 1], pointsZ[nPoint], color);
            DebugManager::AddLine(pointsY[nPoint - 1], pointsY[nPoint], color);
        }
    }

    // Adding last points
    DebugManager::AddLine(pointsZ[0], pointsZ[pointsZ.size() - 1], color);
    DebugManager::AddLine(pointsY[0], pointsY[pointsY.size() - 1], color);

    // Adding light at the center
    glm::vec3 top  (position.x, position.y, position.z + 2.0f * scale);
    glm::vec3 bot  (position.x, position.y, position.z - 2.0f * scale);
    glm::vec3 left (position.x - 1.0f * scale, position.y, position.z);
    glm::vec3 right(position.x + 1.0f * scale, position.y, position.z);
    glm::vec3 front(position.x, position.y + 1.0f * scale, position.z);
    glm::vec3 back (position.x, position.y - 1.0f * scale, position.z);

    glm::vec3 rayLeftStart (left.x - 1.0f,         left.y, left.z);
    glm::vec3 rayLeftEnd   (left.x - 2.0f * scale, left.y, left.z);

    glm::vec3 rayRightStart(right.x + 1.0f,         right.y, right.z);
    glm::vec3 rayRightEnd  (right.x + 2.0f * scale, right.y, right.z);
    glm::vec3 rayFrontStart(front.x, front.y + 1.0f,         front.z);
    glm::vec3 rayFrontEnd  (front.x, front.y + 2.0f * scale, front.z);

    glm::vec3 rayBackStart (back.x, back.y - 1.0f,         back.z);
    glm::vec3 rayBackEnd   (back.x, back.y - 2.0f * scale, back.z);

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

/// \brief Draw a cone in the world
/// \param position The start point of the cone
/// \param radius The base radius of the cone
/// \param topRadius The top radius
/// \param lenght The lenght of the cone
/// \param color The color of the line
void DrawCone(glm::vec3 const& position, float radius,  float topRadius, float lenght, glm::vec3 const& color)
{
#ifdef CARDINAL_DEBUG
    if(!DebugManager::IsGizmoEnabled(DebugManager::EGizmo::Cone))
    {
        return;
    }

    // Compute spherical coordinates
    int pointCount = static_cast<int>(20 * radius); // NOLINT
    float alpha    = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

    std::vector<glm::vec3> points;
    for (int nPoint = 0; nPoint < pointCount; ++nPoint)
    {
        float x1 = position.x + glm::cos(alpha * nPoint) * radius;
        float y1 = position.y + glm::sin(alpha * nPoint) * radius;
        float z1 = position.z;

        points.emplace_back(x1, y1, z1);

        if(nPoint != 0)
        {
            DebugManager::AddLine(points[nPoint - 1], points[nPoint], color);
        }
    }

    // Adding last points
    DebugManager::AddLine(points[0], points[points.size() - 1], color);

    // Compute spherical coordinates
    pointCount = static_cast<int>(32 * topRadius); // NOLINT
    alpha      = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

    points.clear();
    for (int nPoint = 0; nPoint < pointCount; ++nPoint)
    {
        float x1 = position.x + glm::cos(alpha * nPoint) * topRadius;
        float y1 = position.y + glm::sin(alpha * nPoint) * topRadius;
        float z1 = position.z + lenght;

        points.emplace_back(x1, y1, z1);

        if(nPoint != 0)
        {
            DebugManager::AddLine(points[nPoint - 1], points[nPoint], color);
        }
    }

    // Adding last points
    DebugManager::AddLine(points[0], points[points.size() - 1], color);

    // Add 4 four side lines
    DebugManager::AddLine(glm::vec3(position.x + glm::cos(0) * radius,    position.y + glm::sin(0) * radius,    position.z),
                          glm::vec3(position.x + glm::cos(0) * topRadius, position.y + glm::sin(0) * topRadius, position.z + lenght), color);

    DebugManager::AddLine(glm::vec3(position.x + glm::cos(M_PI_2) * radius,    position.y + glm::sin(M_PI_2) * radius,    position.z),
                          glm::vec3(position.x + glm::cos(M_PI_2) * topRadius, position.y + glm::sin(M_PI_2) * topRadius, position.z + lenght), color);

    DebugManager::AddLine(glm::vec3(position.x + glm::cos(M_PI) * radius,    position.y + glm::sin(M_PI) * radius,    position.z),
                          glm::vec3(position.x + glm::cos(M_PI) * topRadius, position.y + glm::sin(M_PI) * topRadius, position.z + lenght), color);

    DebugManager::AddLine(glm::vec3(position.x + glm::cos(M_PI + M_PI_2) * radius,    position.y + glm::sin(M_PI + M_PI_2) * radius,    position.z),
                          glm::vec3(position.x + glm::cos(M_PI + M_PI_2) * topRadius, position.y + glm::sin(M_PI + M_PI_2) * topRadius, position.z + lenght), color);

#endif
}

} // !namespace

} // !namespace