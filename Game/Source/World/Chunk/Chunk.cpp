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

/// \file       Chunk.cpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO


// Game
#include "World/Chunk/Chunk.hpp"

/// \brief Constructor
Chunk::Chunk() // NOLINT
{
    m_chunkIndexX = 0;
    m_chunkIndexY = 0;
    m_chunkIndexZ = 0;

    for(uint i = 0; i < 6; ++i) // NOLINT
        m_neighbors[i] = nullptr;

    m_state = EChunkState::Generated;
}

/// \brief Destructor
Chunk::~Chunk() // NOLINT
{
    // TODO
}

/// \brief Initializes the chunk at the given world
///        chunk coordinates
void Chunk::Initialize(int chunkIndexX, int chunkIndexY, int chunkIndexZ)
{
    m_chunkIndexX = chunkIndexX;
    m_chunkIndexY = chunkIndexY;
    m_chunkIndexZ = chunkIndexZ;

    m_terrainRenderer.SetPosition(glm::vec3(
            chunkIndexX * WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
            chunkIndexY * WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
            chunkIndexZ * WorldSettings::s_chunkSize * ByteCube::s_cubeSize));

    m_grassRenderer.SetPosition(glm::vec3(
            chunkIndexX * WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
            chunkIndexY * WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
            chunkIndexZ * WorldSettings::s_chunkSize * ByteCube::s_cubeSize));

    m_transparentCubeRenderer.SetPosition(glm::vec3(
            chunkIndexX * WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
            chunkIndexY * WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
            chunkIndexZ * WorldSettings::s_chunkSize * ByteCube::s_cubeSize));
}

void Chunk::SetNeighbors(Chunk * neighbors[6])
{
    memcpy(&m_neighbors[0], &neighbors[0], 6 * sizeof(Chunk *));
}

// TODO
void Chunk::Batch()
{
    m_terrainRenderer.Batch(m_cubes, m_neighbors);
    m_grassRenderer.Batch(m_cubes, m_neighbors);
    m_transparentCubeRenderer.Batch(m_cubes, m_neighbors);
}
