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

/// \file       DebugGrid.hpp
/// \date       25/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEBUG_GRID_HPP__
#define CARDINAL_ENGINE_DEBUG_GRID_HPP__

#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class DebugGrid
/// \brief Displays the engine grid
class DebugGrid
{
public:

    /// \brief Initializes the grid from parameters
    /// \param size The number of lines on X & Y
    /// \param spacing The space between two cols & rows
    /// \param color The colors of lines
    void Initialize(int size, float spacing, glm::vec3 const& color);

    /// \brief Draws the grid
    /// \param PV The projection view matrix
    void Draw(glm::mat4 const& PV);

private:

    uint      m_vertexCount;
    uint      m_vao;
    uint      m_vbo;
    uint      m_cbo;
    int       m_matrixID;
    uint      m_shaderID;
};

} // !namespace

#endif // !CARDINAL_ENGINE_DEBUG_GRID_HPP__