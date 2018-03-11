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

/// \file       DebugManager.hpp
/// \date       16/02/2018 
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEBUG_MANAGER_HPP__
#define CARDINAL_ENGINE_DEBUG_MANAGER_HPP__

#include <unordered_map>

#include "Glm/glm/glm.hpp"
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Platform/Configuration/Type.hh"
#include "Runtime/Rendering/Debug/DebugGrid.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class DebugManager
/// \brief Batches and optimizes debug lines
class DebugManager
{
public:


    /// \brief Represents a type of gizmo
    /// \enum EGizmo
    enum EGizmo
    {
        Box,
        Ray,
        Line,
        Axis,
        Grid,
        Cone,
        PointLight,
        DirectionalLight
    };

    /// \brief Adds a line to render for the next frame
    /// \param start The start point of the line
    /// \param end The end point
    /// \param color The color of the line
    static void AddLine(glm::vec3 const& start, glm::vec3 const& end, glm::vec3 const& color);

    /// \brief Enables a gizmo
    /// \param type The gizmo to enable
    static void EnableGizmo(EGizmo type);

    /// \brief Disables a gizmo
    /// \param type The gizmo to disable
    static void DisableGizmo(EGizmo type);

    /// \brief Tells if the given gizmo is enabled
    /// \return True or false
    static bool IsGizmoEnabled(EGizmo type);

private:

    friend class RenderingEngine;

    /// \brief Constructor, allocates buffers
    DebugManager();

    /// \brief Destructor, free buffers
    ~DebugManager();

    /// \brief Initializes the debug manager
    ///        Initializes the manager instance
    static void Initialize();

    /// \brief Destroys the debug manager
    ///        Destroys the manager instance
    static void Shutdown  ();

    /// \brief Clears vertices and colors
    static void Clear();

    /// \brief Updates buffers and setup the shader
    static void Draw(glm::mat4 const& PV);

    uint      m_vertexCount;
    glm::vec3 m_vertices[5000];
    glm::vec3 m_colors  [5000];

    uint      m_vao;
    uint      m_vbo;
    uint      m_cbo;
    int       m_matrixID;
    uint      m_shaderID;

    DebugGrid                        m_grid;
    std::unordered_map<EGizmo, bool> m_activeGizmos;

private:

    static DebugManager * s_pInstance;
};

} // !namespace 

#endif // !CARDINAL_ENGINE_DEBUG_MANAGER_HPP__