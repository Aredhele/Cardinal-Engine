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

// Engine
#include "Runtime/Core/Maths/Noise/NYPerlin.hpp"

// Game
#include "World/Chunk/Chunk.hpp"

/* static */ NYPerlin Chunk::s_perlin;

/// \brief Constructor
Chunk::Chunk() // NOLINT
{
    m_chunkIndexX = 0;
    m_chunkIndexY = 0;
    m_chunkIndexZ = 0;

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

    GenerateChunk();
    Batch();
}

// TODO
void Chunk::GenerateChunk()
{
    GenerateTerrain();
    // TODO
}

// TODO
void Chunk::GenerateTerrain()
{
    float TweakA = 16.0f;
    float TweakB = 10.0f;
    float TweakC = 300.0f;

    for(int x = 0; x < WorldSettings::s_chunkSize; ++x)
    {
        for(int y = 0; y < WorldSettings::s_chunkSize; ++y)
        {
            for(int z = 0; z < WorldSettings::s_chunkSize; ++z)
            {
                int worldX = x + m_chunkIndexX * (int)WorldSettings::s_chunkSize;
                int worldY = y + m_chunkIndexY * (int)WorldSettings::s_chunkSize;
                int worldZ = z + m_chunkIndexZ * (int)WorldSettings::s_chunkSize;

                ByteCube * pCube = &m_cubes[x][y][z];

                float modifier = 0.04;
                float sample   = Chunk::s_perlin.sample(modifier * worldX, modifier * worldY, modifier * worldZ);
                sample        /= pow((float)worldZ / (float)WorldSettings::s_matHeightCubes, TweakA) / TweakB + TweakC;

                if (sample < 0.9f)
                {
                    pCube->SetType(ByteCube::EType::Air);
                    pCube->Enable();
                }
                else
                {
                    pCube->SetType(ByteCube::EType::Dirt);
                    pCube->Enable();
                }
            }
        }
    }
}

// TODO
void Chunk::Batch()
{
    m_terrainRenderer.Batch(m_cubes);
}
