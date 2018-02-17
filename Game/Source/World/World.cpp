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

#include "World/World.hpp"

/// \brief Default constructor
World::World()
{
    m_chunks = nullptr;

    m_worldText       = cardinal::RenderingEngine::AllocateTextRenderer();
    m_cubeText        = cardinal::RenderingEngine::AllocateTextRenderer();
    m_chunkText       = cardinal::RenderingEngine::AllocateTextRenderer();
    m_playerCubeText  = cardinal::RenderingEngine::AllocateTextRenderer();
    m_playerChunkText = cardinal::RenderingEngine::AllocateTextRenderer();

    m_worldText->Initialize();
    m_cubeText->Initialize();
    m_chunkText->Initialize();
    m_playerCubeText->Initialize();
    m_playerChunkText->Initialize();

    m_worldText->SetText("World info",          730, 580, 14, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_cubeText->SetText ("Cubes count  : 0",    680, 560, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_chunkText->SetText("Chunks count : 0",    680, 545, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerChunkText->SetText("Cube : 0 0 0",  680, 530, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerCubeText->SetText ("Chunk : 0 0 0", 680, 515, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

/// \brief Destructor
World::~World() // NOLINT
{
    // TODO : Delete chunks
}

/// \brief Updates the world from the character position
/// \param position The position of the character
/// \param dt The elasped time
void World::Update(const glm::vec3 &position, float dt)
{
    // Updating debug text
    // Computing player position
    int posX = (int)position.x / ByteCube::s_cubeSize;
    int posY = (int)position.y / ByteCube::s_cubeSize;
    int posZ = (int)position.z / ByteCube::s_cubeSize;

    std::string _cube  = "Cube : "  + std::to_string(posX) + " " + std::to_string(posY) + " " + std::to_string(posZ);
    std::string _chunk = "Chunk : " + std::to_string(posX / (int)WorldSettings::s_chunkSize) + " " +
                                      std::to_string(posY / (int)WorldSettings::s_chunkSize) + " " +
                                      std::to_string(posZ / (int)WorldSettings::s_chunkSize);

    m_playerChunkText->SetText(_cube.c_str(),  680, 530, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerCubeText->SetText (_chunk.c_str(), 680, 515, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Debug draw
    for(uint x = 0; x < World::s_matSize; ++x)
    {
        for(uint y = 0; y < World::s_matSize; ++y)
        {
            for(uint z = 0; z < World::s_matHeight; ++z)
            {
                cardinal::debug::DrawBox(glm::vec3(
                        (x * WorldSettings::s_chunkSize * ByteCube::s_cubeSize) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f,
                        (y * WorldSettings::s_chunkSize * ByteCube::s_cubeSize) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f,
                        (z * WorldSettings::s_chunkSize * ByteCube::s_cubeSize) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f),
                                         WorldSettings::s_chunkSize * ByteCube::s_cubeSize,
                                         WorldSettings::s_chunkSize * ByteCube::s_cubeSize, glm::vec3(1.0f, 0.5f, 0.7f));
            }
        }
    }
}

/// \brief Creates the initial world
void World::Initialize()
{
    WorldBuffers::Initialize();

    cardinal::Logger::LogInfo("Allocating chunks ....");

    // Allocating memory for chunks
    m_chunks = new Chunk ***[World::s_matSize];
    for(int i = 0; i < World::s_matSize; ++i)
    {
        m_chunks[i] =  new Chunk **[World::s_matSize];
        for(int j = 0; j < World::s_matSize; ++j)
        {
            m_chunks[i][j] = new Chunk *[World::s_matHeight];

            for(int k = 0; k < World::s_matHeight; ++k)
            {
                m_chunks[i][j][k] = new Chunk();
                m_chunks[i][j][k]->Initialize(i, j, k);
            }
        }
    }

    cardinal::Logger::LogInfo("%d chunks allocated",
                              World::s_matSize *
                              World::s_matSize *
                              World::s_matHeight);

    // Settings debug text
    std::string _cubes  = "Cubes count  : " + std::to_string(World::s_matSize * World::s_matSize * World::s_matHeight * WorldSettings::s_chunkBlockCount);
    std::string _chunks = "Chunks count : " + std::to_string(World::s_matSize * World::s_matSize * World::s_matHeight);

    m_cubeText->SetText (_cubes.c_str(),  680, 560, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_chunkText->SetText(_chunks.c_str(), 680, 545, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}
