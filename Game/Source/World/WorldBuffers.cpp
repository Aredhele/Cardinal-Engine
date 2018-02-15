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

/// \file       WorldBuffers.cpp
/// \date       15/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#include "World/WorldBuffers.hpp"
#include "World/WorldSettings.hpp"

/* static */ std::vector<glm::vec2>  WorldBuffers::s_chunkUVsBuffer;
/* static */ std::vector<glm::vec3>  WorldBuffers::s_chunkVertexBuffer;
/* static */ std::vector<ushort>     WorldBuffers::s_chunkIndexesBuffer;
/* static */ std::vector<glm::vec2>  WorldBuffers::s_chunkIndexedUVsBuffer;
/* static */ std::vector<glm::vec3>  WorldBuffers::s_chunkIndexedVertexBuffer;

/// \brief Initializes all world buffers
/* static */ void WorldBuffers::Initialize()
{
    s_chunkVertexBuffer = std::vector<glm::vec3>(WorldSettings::s_chunkVertexCount);
    s_chunkUVsBuffer    = std::vector<glm::vec2>(WorldSettings::s_chunkVertexCount);

    s_chunkIndexesBuffer.reserve       (WorldSettings::s_chunkVertexCount);
    s_chunkIndexedUVsBuffer.reserve    (WorldSettings::s_chunkUVsCount);
    s_chunkIndexedVertexBuffer.reserve (WorldSettings::s_chunkVertexCount);

    cardinal::Logger::LogInfo("World static buffers initialized");
}
