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

/// \file       WorldBuffers.hpp
/// \date       15/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_WORLD_BUFFERS_HPP__
#define CARDINAL_ENGINE_WORLD_BUFFERS_HPP__

#include <vector>
#include "Glm/glm/glm.hpp"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Platform/Configuration/Configuration.hh"

#include "World/Detail/Grass.hpp"

/// \class WorldBuffers
/// \brief Stores usefull buffers to avoid memory allocations
class WorldBuffers
{
public:

    // Terrain
    static std::vector<glm::vec2> s_chunkUVsBuffer;
    static std::vector<glm::vec3> s_chunkVertexBuffer;
    static std::vector<ushort>    s_chunkIndexesBuffer;
    static std::vector<glm::vec2> s_chunkIndexedUVsBuffer;
    static std::vector<glm::vec3> s_chunkIndexedVertexBuffer;

    // Details
    static std::vector<Grass> s_grassBuffer;

public:

    /// \brief Initializes all world buffers
    static void Initialize();
};

#endif // !CARDINAL_ENGINE_WORLD_BUFFERS_HPP__