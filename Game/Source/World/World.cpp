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

/// \file       World.cpp
/// \date       17/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#include <iostream>
#include "World/World.hpp"

/// \brief Default constructor
World::World()
{
    m_chunks = nullptr;

    m_worldText       = cardinal::RenderingEngine::AllocateTextRenderer();
    m_cubeText        = cardinal::RenderingEngine::AllocateTextRenderer();
    m_chunkText       = cardinal::RenderingEngine::AllocateTextRenderer();


    m_worldText->Initialize();
    m_cubeText->Initialize();
    m_chunkText->Initialize();

    m_worldText->SetText("World info",          730, 580, 14, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_cubeText->SetText ("Cubes count  : 0",    680, 560, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_chunkText->SetText("Chunks count : 0",    680, 545, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

/// \brief Destructor
World::~World() // NOLINT
{
    // TODO : Delete chunks
}



/// \brief Creates the initial world
/// \param position The initial player position
void World::Initialize()
{
    auto worldBegin = std::chrono::steady_clock::now();

    WorldBuffers::Initialize();
    cardinal::Logger::LogInfo("Allocating chunks ....");

    // Allocating memory for chunks

    m_chunks = new Chunk ***[WorldSettings::s_matSize];
    for(int i = 0; i < WorldSettings::s_matSize; ++i)
    {
        m_chunks[i] =  new Chunk **[WorldSettings::s_matSize];
        for(int j = 0; j < WorldSettings::s_matSize; ++j)
        {
            m_chunks[i][j] = new Chunk *[WorldSettings::s_matHeight];

            for(int k = 0; k < WorldSettings::s_matHeight; ++k)
            {
                m_chunks[i][j][k] = new Chunk();
                m_chunks[i][j][k]->Initialize(i, j, k);
            }
        }
    }

    Chunk * neighbors[6];
    for(int i = 0; i < WorldSettings::s_matSize; ++i)
    {
        for(int j = 0; j < WorldSettings::s_matSize; ++j)
        {
            for(int k = 0; k < WorldSettings::s_matHeight; ++k)
            {
                GetNeighbors(i, j, k, neighbors);
                m_chunks[i][j][k]->SetNeighbors(neighbors);
            }
        }
    }

    cardinal::Logger::LogInfo("%d chunks allocated",
                              WorldSettings::s_matSize *
                              WorldSettings::s_matSize *
                              WorldSettings::s_matHeight);

    // Settings debug text
    std::string _cubes  = "Cubes count  : " + std::to_string(WorldSettings::s_matSize * WorldSettings::s_matSize * WorldSettings::s_matHeight * WorldSettings::s_chunkBlockCount);
    std::string _chunks = "Chunks count : " + std::to_string(WorldSettings::s_matSize * WorldSettings::s_matSize * WorldSettings::s_matHeight);

    m_cubeText->SetText (_cubes.c_str(),  680, 560, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_chunkText->SetText(_chunks.c_str(), 680, 545, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    /*int chunkX = ((int)position.x / ByteCube::s_cubeSize) / (int)WorldSettings::s_chunkSize;
    int chunkY = ((int)position.y / ByteCube::s_cubeSize) / (int)WorldSettings::s_chunkSize;
    int chunkZ = ((int)position.z / ByteCube::s_cubeSize) / (int)WorldSettings::s_chunkSize;

    m_lastPlayerPos.x = chunkX;
    m_lastPlayerPos.y = chunkY;
    m_lastPlayerPos.z = chunkZ;*/

    auto worldEnd = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(worldEnd - worldBegin);

    cardinal::Logger::LogInfo("World generated in %d ms", elapsed);
}

void World::GetNeighbors(int x, int y, int z, Chunk * neighbors[6])
{
    if(x - 1 >= 0                        ) { neighbors[0] = m_chunks[x - 1][y][z]; } else { neighbors[0] = nullptr; }
    if(x + 1 < WorldSettings::s_matSize  ) { neighbors[1] = m_chunks[x + 1][y][z]; } else { neighbors[1] = nullptr; }
    if(y - 1 >= 0                        ) { neighbors[2] = m_chunks[x][y - 1][z]; } else { neighbors[2] = nullptr; }
    if(y + 1 < WorldSettings::s_matSize  ) { neighbors[3] = m_chunks[x][y + 1][z]; } else { neighbors[3] = nullptr; }
    if(z - 1 >= 0                        ) { neighbors[4] = m_chunks[x][y][z - 1]; } else { neighbors[4] = nullptr; }
    if(z + 1 < WorldSettings::s_matHeight) { neighbors[5] = m_chunks[x][y][z + 1]; } else { neighbors[5] = nullptr; }
}

void World::Batch()
{
    for(int i = 0; i < WorldSettings::s_matSize; ++i)
    {
        for(int j = 0; j < WorldSettings::s_matSize; ++j)
        {
            for(int k = 0; k < WorldSettings::s_matHeight; ++k)
            {
                m_chunks[i][j][k]->Batch();
            }
        }
    }
}
